% Temporary numbers to test functionality.
m = 10; n = 5;
% Creating random matrix and vector.
A = randn(m,n);
b = randn(n,1);
% Calculating execution time with timeit.
x = @() mv_ij(A,b); rt_mv_ij = timeit(x);
y = @() mv_ji(A,b); rt_mv_ji = timeit(y);
z = @() mtimes(A,b); rt_mv_ab = timeit(z);
% Calculating flops.
flops = 2 * m * n;
% Calculating MFlop/s for each function.
ij_mflops = (flops/rt_mv_ij) * 10e-6;
ji_mflops = (flops/rt_mv_ji) * 10e-6;
ab_mflops = (flops/rt_mv_ab) * 10e-6;
% Printing the requested results.
fprintf('-----------------------------------------------\n')
fprintf('Computing Matrix-Vector Multiplication c = A*b\n')
fprintf('-----------------------------------------------\n')
fprintf('>>> Number of matrix rows m: %i\n',m)
fprintf('>>> Number of matrix columns n: %i\n',n)
fprintf('>>> Number of flops: %i\n\n',flops)
fprintf('Method\t\t   CPU (sec)   \t\tMFlop/s\n')
fprintf('------\t\t-------------- \t\t-------\n')
fprintf('mv_ij \t\t %d  \t\t %i\n',rt_mv_ij,round(ij_mflops))
fprintf('mv_ji \t\t %d  \t\t %i\n',rt_mv_ji,round(ji_mflops))
fprintf('mv_ab \t\t %d  \t\t %i\n',rt_mv_ab,round(ab_mflops))
