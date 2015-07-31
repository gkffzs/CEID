% Creating a text file for the results.
file_id = fopen('2_3_a_a.txt','w');
% Finding polynomial coefficients from given roots.
z = [1:20]; p = poly(z);
% Printing initial polynomial coefficients.
fprintf(file_id, '------------------------------------------\n');
fprintf(file_id, '||||||||| INITIAL COEFFICIENTS |||||||||||\n');
fprintf(file_id, '------------------------------------------\n');
fprintf(file_id, '-----[ p(1,:) ]----#\n');
fprintf(file_id, '%3.12e\n', p);
% Specifying required disturbances.
e = [10^(-8) (-10^3) 10^10]; er = p*(2^(-52));
% Preallocating space for later calculations.
g = zeros(5,21); f = zeros(5,21); r = zeros(5,20);
% Calculating coefficients of disturbance polynomials.
g(1,(21-19)) = 1;
g(2,(21-11)) = 1;
g(3,(21-1)) = 1;
g(4,2:21) = 1;
g(5,2:21) = 1;
% Calculating final coefficients.
f(1,:) = p + g(1,:).*e(1);
f(2,:) = p + g(2,:).*e(2);
f(3,:) = p + g(3,:).*e(3);
f(4,:) = p + g(4,:).*e(1);
f(5,:) = p + g(5,:).*er;
% Printing the perturbed coefficients.
fprintf(file_id, '\n');
fprintf(file_id, '------------------------------------------\n');
fprintf(file_id, '||||||||| PERTURBED COEFFICIENTS |||||||||\n');
fprintf(file_id, '------------------------------------------\n');
for i=1:5
    fprintf(file_id, '-----[ f(%d,:) ]----#\n', i);
    for j=1:21
        fprintf(file_id, '%3.12e\n', f(i,j));
    end
end
% Finding the roots of the new polynomials.
r(1,:) = roots(f(1,:));
r(2,:) = roots(f(2,:));
r(3,:) = roots(f(3,:));
r(4,:) = roots(f(4,:));
r(5,:) = roots(f(5,:));
% Printing the roots of the perturbed polynomials.
fprintf(file_id, '\n');
fprintf(file_id, '------------------------------------------\n');
fprintf(file_id, '|||||||||||||| NEW ROOTS |||||||||||||||||\n');
fprintf(file_id, '------------------------------------------\n');
for i=1:5
    fprintf(file_id, '-----[ r(%d,:) ]----#\n', i);
    for j=1:20
        fprintf(file_id, '%3.12e + ', r(i,j));
        fprintf(file_id, '(%3.12e)i\n', imag(r(i,j)));
    end
end
% Finding required errors.
r_e = zeros(5,20); k_r = zeros(5,20);
has_imag_roots = 0; % To check for imaginary roots.
temp_r = zeros(5,20); % Temporarily save roots.
for i=1:5
    % Checking if there are any imaginary roots.
    for j=1:20
       if (imag(r(i,j)) > 0)
           has_imag_roots = 1;
           break;
       end
    end
    % Two kinds of calculations.
    if (has_imag_roots == 1) % 1) For both roots.
        temp_r(i,:) = sort(r(i,:),'descend');
        for j=1:20, r(i,j) = temp_r(i,j); end
        k_r(i,:) = [20:-1:1];
        for j=1:20
            r_e(i,j) = abs(k_r(i,j)-r(i,j))/abs(k_r(i,j));
        end
    else % 2) For real roots. 
        for j=1:20
            [dif,pos] = min(abs(z-r(i,j)));
            r_e(i,j) = abs(z(pos)-r(i,j))/abs(z(pos));
            k_r(i,j) = z(pos);
        end
    end
    % Setting flag to zero.
    has_imag_roots = 0;
end
% Sorting roots based on previous errors.
s_r = zeros(5,20); s_r_e = zeros(5,20);
s_k_r = zeros(5,20); ix = zeros(5,20);
for i=1:5
    [s_r_e(i,:),ix(i,:)] = sort(r_e(i,:),'descend');
    s_r(i,:) = r(i,ix(i,:));
    s_k_r(i,:) = k_r(i,ix(i,:));
end
% Printing sorted roots, known roots and their relative error.
fprintf(file_id, '\n');
fprintf(file_id, '------------------------------------------\n');
fprintf(file_id, '|| SORTED ROOTS || KNOWN ROOTS || ERROR ||\n');
fprintf(file_id, '------------------------------------------\n');
for i=1:5
    fprintf(file_id, '---[ s_r, s_k_r, s_r_e (%d) ]-----#\n', i);
    for j=1:20
        fprintf(file_id, '%3.3e + ', s_r(i,j));
        fprintf(file_id, '(%3.3e)i  ||  ', imag(s_r(i,j)));
        fprintf(file_id, '%d  ||  ', s_k_r(i,j));
        fprintf(file_id, '%3.3e\n', s_r_e(i,j));
    end
end
% Closing text file with results.
fclose(file_id);
% Plotting known and found roots.
figure;
plot(real(s_r(1,:)), imag(s_r(1,:)),'bo','MarkerSize',6); hold on;
plot(real(s_k_r(1,:)), imag(s_k_r(1,:)),'r*','MarkerSize',5);
hold off; legend('found','known','Location','Best'); grid on;
title('Roots (#1)'); xlabel('real'); ylabel('imag');
figure;
plot(real(s_r(2,:)), imag(s_r(2,:)),'bo','MarkerSize',6); hold on;
plot(real(s_k_r(2,:)), imag(s_k_r(2,:)),'r*','MarkerSize',5);
hold off; legend('found','known','Location','Best'); grid on;
title('Roots (#2)'); xlabel('real'); ylabel('imag');
figure;
plot(real(s_r(3,:)), imag(s_r(3,:)),'bo','MarkerSize',6); hold on;
plot(real(s_k_r(3,:)), imag(s_k_r(3,:)),'r*','MarkerSize',5);
hold off; legend('found','known','Location','Best'); grid on;
title('Roots (#3)'); xlabel('real'); ylabel('imag');
figure;
plot(real(s_r(4,:)), imag(s_r(4,:)),'bo','MarkerSize',6); hold on;
plot(real(s_k_r(4,:)), imag(s_k_r(4,:)),'r*','MarkerSize',5);
hold off; legend('found','known','Location','Best'); grid on;
title('Roots (#4)'); xlabel('real'); ylabel('imag');
figure;
plot(real(s_r(5,:)), imag(s_r(5,:)),'bo','MarkerSize',6); hold on;
plot(real(s_k_r(5,:)), imag(s_k_r(5,:)),'r*','MarkerSize',5);
hold off; legend('found','known','Location','Best'); grid on;
title('Roots (#5)'); xlabel('real'); ylabel('imag');
