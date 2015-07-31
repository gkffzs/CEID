% Variable for random matrix sizes.
matrix_size = 200:200:1200;

% Initialization of rt_lu to store results.
rt_lu = zeros(1,6);
for j = 1:6 % Loop for lu(A).
    % Random matrix.
    A = randn(matrix_size(j));
    % Time calculation with timeit.
    x = @() lu(A);
    rt_lu(j) = timeit(x,2);
end
% Initialization of rt_qr to store results.
rt_qr = zeros(1,6);
for j = 1:6 % Loop for qr(A).
    % Random matrix.
    A = randn(matrix_size(j));
    % Time calculation with timeit.
    x = @() qr(A);
    rt_qr(j) = timeit(x,2);
end
% Initialization of rt_svd to store results.
rt_svd = zeros(1,6);
for j = 1:6 % Loop for svd(A).
    % Random matrix.
    A = randn(matrix_size(j));
    % Time calculation with timeit.
    x = @() svd(A);
    rt_svd(j) = timeit(x,3);
end
% Initialization of rt_eig to store results.
rt_eig = zeros(1,6);
for j = 1:6 % Loop for eig(A).
    % Random matrix.
    A = randn(matrix_size(j));
    % Time calculation with timeit.
    x = @() eig(A);
    rt_eig(j) = timeit(x,2);
end

figure; % Plotting the results.
plot(matrix_size,rt_lu,'b*-',...
     matrix_size,rt_qr,'r+-',...
     matrix_size,rt_svd,'gx-',...
     matrix_size,rt_eig,'cd-',...
     'LineWidth',2);
title('2-ii-c','fontWeight','bold');
xlabel('Matrix size n');
ylabel('Runtime (sec)');
legend('lu(A)','qr(A)','svd(A)','eig(A)',...
       'Location','NorthWest');
grid on;