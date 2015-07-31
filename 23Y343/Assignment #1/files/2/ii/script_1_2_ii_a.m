% Variable for random matrix sizes.
matrix_size = 200:200:1200;
% A little warm-up for tic-toc.
tic; toc;

% Initialization of rt_lu to store results.
rt_lu = zeros(1,6);
for j = 1:6 % Loop for lu(A).
    % Random matrix and lu(A) warm-up.
    A = randn(matrix_size(j)); [L,U] = lu(A);
    % Time calculation with tic-toc.
    tic; [L,U] = lu(A); rt_lu(j) = toc;
end
% Initialization of rt_qr to store results.
rt_qr = zeros(1,6);
for j = 1:6 % Loop for qr(A).
    % Random matrix and qr(A) warm-up.
    A = randn(matrix_size(j)); [Q,R] = qr(A);
    % Time calculation with tic-toc.
    tic; [Q,R] = qr(A); rt_qr(j) = toc;
end
% Initialization of rt_svd to store results.
rt_svd = zeros(1,6);
for j = 1:6 % Loop for svd(A).
    % Random matrix and svd(A) warm-up.
    A = randn(matrix_size(j)); [U,S,V] = svd(A);
    % Time calculation with tic-toc.
    tic; [U,S,V] = svd(A); rt_svd(j) = toc;
end
% Initialization of rt_eig to store results.
rt_eig = zeros(1,6);
for j = 1:6 % Loop for eig(A).
    % Random matrix and eig(A) warm-up.
    A = randn(matrix_size(j)); [V,D] = eig(A);
    % Time calculation with tic-toc.
    tic; [V,D] = eig(A); rt_eig(j) = toc;
end

figure; % Plotting the results.
plot(matrix_size,rt_lu,'b*-',...
     matrix_size,rt_qr,'r+-',...
     matrix_size,rt_svd,'gx-',...
     matrix_size,rt_eig,'cd-',...
     'LineWidth',2);
title('2-ii-a','fontWeight','bold');
xlabel('Matrix size n');
ylabel('Runtime (sec)');
legend('lu(A)','qr(A)','svd(A)','eig(A)',...
       'Location','NorthWest');
grid on;