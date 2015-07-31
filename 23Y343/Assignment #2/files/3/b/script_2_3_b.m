% Creating a text file for the results.
file_id = fopen('2_3_b.txt','w');
fprintf(file_id, '------------------------------------------\n');
fprintf(file_id, '|||||||||||||||| RESULTS |||||||||||||||||\n');
fprintf(file_id, '------------------------------------------\n');
% Finding polynomial coefficients from given roots.
z = [1:10]; p = poly(z);
% Specifying x values as input.
x = [1+eps 1+10^(-8) 1.5 5.5 9+10^(-8) 9+eps(9)];
rd = zeros(6,1); % For values using polynomial form.
rp = zeros(6,1); % For values using product form.
re = zeros(6,1); % For the relative error.
cond_num = zeros(6,1); % For the condition number.
n = length(z); u = eps; % Specifying n and u.
g2n = (2*n*u) / (1-2*n*u); % Barrier of back-error.
barrier = zeros(6,1); % (g2n * cond_num)
for i=1:6 % Calculations.
    rd(i) = polyval(p,x(i)); % Calculating p(x). (1)
    rp(i) = prod(x(i)-[1:10]); % Calculating p(x). (2)
    re(i) = abs(rp(i)-rd(i)) / abs(rp(i)); % Relative error.
    temp_sum = 0;
    for k=1:n+1 % Temporary summary for condition number.
        temp_sum = temp_sum + abs(p(k))*abs(x(i)^(n+1-k));
    end
    cond_num(i) = temp_sum / abs(rp(i)); % Condition number.
    barrier(i) = g2n * cond_num(i); % Barrier of front-error.
    % Printing results to file.
    fprintf(file_id, 'x(%d): %3.15e\n',i,x(i));
    fprintf(file_id, 'rd(%d): %3.15e\n',i,rd(i));
    fprintf(file_id, 'rp(%d): %3.15e\n',i,rp(i));
    fprintf(file_id, 're(%d): %3.15e\n',i,re(i));
    fprintf(file_id, 'cond_num(%d): %3.15e\n',i,cond_num(i));
    fprintf(file_id, 'barrier(%d): %3.15e\n',i,barrier(i));
    fprintf(file_id, '---------------------------*\n');
end
% Closing text file with results.
fclose(file_id);