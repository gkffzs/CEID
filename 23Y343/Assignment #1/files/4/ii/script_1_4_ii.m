% Several matrix sizes.
n = [50;100;200;400;800];
%Initialization of rt_ab to store results.
rt_ab = zeros(5,1);
for i=1:5 % Loop to calculate execution time.
    % Random matrix and vector.
    A = randn(n(i),n(i));
    b = randn(n(i),1);
    % Calculating execution time with timeit.
    x = @() mtimes(A,b);
    rt_ab(i) = timeit(x);
end

% Calculating several polynomials.
P1 = polyfit(n,rt_ab,1);
r1 = polyval(P1,n);
P2 = polyfit(n,rt_ab,2);
r2 = polyval(P2,n);
P3 = polyfit(n,rt_ab,3);
r3 = polyval(P3,n);
P4 = polyfit(n,rt_ab,4);
r4 = polyval(P4,n);

% Plotting graphs for each polynomial.
figure;
subplot(4,1,1); % Plot for first class.
plot(n,rt_ab,'bo--',n,r1,'rx-','LineWidth',2);
title('a_{1}n+a_{0}','fontWeight','bold');
xlabel('n'); ylabel('sec'); grid on;
subplot(4,1,2); % Plot for second class.
plot(n,rt_ab,'bo--',n,r2,'rx-','LineWidth',2);
title('a_{2}n^{2}+a_{1}n+a_{0}','fontWeight','bold');
xlabel('n'); ylabel('sec'); grid on;
subplot(4,1,3); % Plot for third class.
plot(n,rt_ab,'bo--',n,r3,'rx-','LineWidth',2);
title('a_{3}n^{3}+a_{2}n^{2}+a_{1}n+a_{0}',...
      'fontWeight','bold');
xlabel('n'); ylabel('sec'); grid on;
subplot(4,1,4); % Plot for fourth class.
plot(n,rt_ab,'bo--',n,r4,'rx-','LineWidth',2);
title('a_{4}n^{4}+a_{3}n^{3}+a_{2}n^{2}+a_{1}n+a_{0}',...
      'fontWeight','bold');
xlabel('n'); ylabel('sec'); grid on;

figure; % Plotting graphs to find complexity.
subplot(2,2,1); % Plot for first class.
semilogy(n,(rt_ab./n),'x-','LineWidth',2);
title('t/n','fontWeight','bold');
xlabel('n'); ylabel('sec');
subplot(2,2,2); % Plot for second class.
semilogy(n,(rt_ab./(n.^2)),'x-','LineWidth',2);
title('t/n^2','fontWeight','bold');
xlabel('n'); ylabel('sec');
subplot(2,2,3); % Plot for third class.
semilogy(n,(rt_ab./(n.^3)),'x-','LineWidth',2);
title('t/n^3','fontWeight','bold');
xlabel('n'); ylabel('sec');
subplot(2,2,4); % Plot for fourth class.
semilogy(n,(rt_ab./(n.^4)),'x-','LineWidth',2);
title('t/n^4','fontWeight','bold');
xlabel('n'); ylabel('sec');
