% Several sizes of matrices.
m = 2.^[4:2:10];
n = m;
% Initialization of matrices to save results.
rt_mv_ij = zeros(4,4);
rt_mv_ji = zeros(4,4);
rt_mv_ab = zeros(4,4);
flops = zeros(4,4);
ij_mflops = zeros(4,4);
ji_mflops = zeros(4,4);
ab_mflops = zeros(4,4);
% Loops for all possible sizes.
for k = 1:4 % 16 different pairs.
    for l = 1:4
        % Creating random matrices.
        A = randn(m(k),n(l));
        b = randn(n(l),1);
        % Calculating execution time with timeit.
        x = @() mv_ij(A,b); rt_mv_ij(k,l) =  timeit(x);
        y = @() mv_ji(A,b); rt_mv_ji(k,l) = timeit(y);
        z = @() mtimes(A,b); rt_mv_ab(k,l) = timeit(z);
        % Calculating flops.
        flops(k,l) = 2 * m(k) * n(l);
        % Calculating MFlop/s for each function.
        ij_mflops(k,l) = (flops(k,l)/rt_mv_ij(k,l)) * 10e-6;
        ji_mflops(k,l) = (flops(k,l)/rt_mv_ji(k,l)) * 10e-6;
        ab_mflops(k,l) = (flops(k,l)/rt_mv_ab(k,l)) * 10e-6;
        % Printing the requested results.
        fprintf('----------------------------------------------\n')
        fprintf('Computing Matrix-Vector Multiplication c = A*b\n')
        fprintf('----------------------------------------------\n')
        fprintf('>>> Number of matrix rows m: %i\n',m(k))
        fprintf('>>> Number of matrix columns n: %i\n',n(l))
        fprintf('>>> Number of flops: %i\n\n',flops(k,l))
        fprintf('Method\t\t   CPU (sec)   \t\tMFlop/s\n')
        fprintf('------\t\t-------------- \t\t-------\n')
        fprintf('mv_ij \t\t %d  \t\t %i\n',...
                 rt_mv_ij(k,l),round(ij_mflops(k,l)))
        fprintf('mv_ji \t\t %d  \t\t %i\n',...
                 rt_mv_ji(k,l),round(ji_mflops(k,l)))
        fprintf('mv_ab \t\t %d  \t\t %i\n',...
                 rt_mv_ab(k,l),round(ab_mflops(k,l)))
    end
end

% Plotting figure for time.
figure; % Main figure.
subplot(2,2,1); % Plot for m=2^4.
plot(n,rt_mv_ij(1,:),'b*-',...
     n,rt_mv_ji(1,:),'gx-',...
     n,rt_mv_ab(1,:),'r+-',...
     'LineWidth',2);
title('Time for m=2^4','fontWeight','bold');
xlabel('n'); ylabel('sec');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','NorthWest');
grid on; axis tight;
subplot(2,2,2); % Plot for m=2^6.
plot(n,rt_mv_ij(2,:),'b*-',...
     n,rt_mv_ji(2,:),'gx-',...
     n,rt_mv_ab(2,:),'r+-',...
     'LineWidth',2);
title('Time for m=2^6','fontWeight','bold');
xlabel('n'); ylabel('sec');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','NorthWest');
grid on; axis tight;
subplot(2,2,3); % Plot for m=2^8.
plot(n,rt_mv_ij(3,:),'b*-',...
     n,rt_mv_ji(3,:),'gx-',...
     n,rt_mv_ab(3,:),'r+-',...
     'LineWidth',2);
title('Time for m=2^8','fontWeight','bold');
xlabel('n'); ylabel('sec');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','NorthWest');
grid on; axis tight;
subplot(2,2,4); % Plot for m=2^10.
plot(n,rt_mv_ij(4,:),'b*-',...
     n,rt_mv_ji(4,:),'gx-',...
     n,rt_mv_ab(4,:),'r+-',...
     'LineWidth',2);
title('Time for m=2^1^0','fontWeight','bold');
xlabel('n'); ylabel('sec');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','NorthWest');
grid on; axis tight;

% Plotting figure for MFlop/s.
figure; % Main figure.
subplot(2,2,1); % Plot for m=2^4.
plot(n,ij_mflops(1,:),'b*-',...
     n,ji_mflops(1,:),'gx-',...
     n,ab_mflops(1,:),'r+-',...
     'LineWidth',2);
title('MFlop/s for m=2^4','fontWeight','bold');
xlabel('n'); ylabel('MFlop/s');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','NorthWest');
grid on; axis tight;
subplot(2,2,2); % Plot for m=2^6.
plot(n,ij_mflops(2,:),'b*-',...
     n,ji_mflops(2,:),'gx-',...
     n,ab_mflops(2,:),'r+-',...
     'LineWidth',2);
title('MFlop/s for m=2^6','fontWeight','bold');
xlabel('n'); ylabel('MFlop/s');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','NorthWest');
grid on; axis tight;
subplot(2,2,3) % Plot for m=2^8.
plot(n,ij_mflops(3,:),'b*-',...
     n,ji_mflops(3,:),'gx-',...
     n,ab_mflops(3,:),'r+-',...
     'LineWidth',2);
title('MFlop/s for m=2^8','fontWeight','bold');
xlabel('n'); ylabel('MFlop/s');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','NorthWest');
grid on; axis tight;
subplot(2,2,4) % Plot for m=2^10.
plot(n,ij_mflops(4,:),'b*-',...
     n,ji_mflops(4,:),'gx-',...
     n,ab_mflops(4,:),'r+-',...
     'LineWidth',2);
title('MFlop/s for m=2^1^0','fontWeight','bold');
xlabel('n'); ylabel('MFlop/s');
legend('mv\_ij','mv\_ji','mv\_ab',...
       'Location','Best');
grid on; axis tight;
