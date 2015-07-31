% Variable for random matrix sizes.
matrix_size = 200:200:1200;
% A little warm-up for tic-toc.
tic; toc;

% Initialization of rt_lu to store results.
rt_lu = zeros(1,6);
for j = 1:6 % Loop for lu(A).
    A = randn(matrix_size(j));
    % lu(A) warm-up and initialization.
    [L,U] = lu(A); sum = 0;
    for i = 1:20 % Counting 20 times.
        % Time calculation with tic-toc.
        tic; [L,U] = lu(A);
        sum = sum + toc; % Increasing sum.
    end
    rt_lu(j) = sum / 20; % Calcuating median.
end
% Initialization of rt_qr to store results.
rt_qr = zeros(1,6);
for j = 1:6 % Loop for qr(A).
    A = randn(matrix_size(j));
    % qr(A) warm-up and initialization.
    [Q,R] = qr(A); sum = 0;
    for i = 1:20 % Counting 20 times.
        % Time calculation with tic-toc.
        tic; [Q,R] = qr(A);
        sum = sum + toc; % Increasing sum.
    end
    rt_qr(j) = sum / 20; % Calcuating median.
end
% Initialization of rt_svd to store results.
rt_svd = zeros(1,6);
for j = 1:6 % Loop for svd(A).
    A = randn(matrix_size(j));
    % svd(A) warm-up and initialization.
    [U,S,V] = svd(A); sum = 0;
    for i = 1:20 % Counting 20 times.
        % Time calculation with tic-toc.
        tic; [U,S,V] = svd(A);
        sum = sum + toc; % Increasing sum.
    end
    rt_svd(j) = sum / 20; % Calcuating median.
end
% Initialization of rt_eig to store results.
rt_eig = zeros(1,6);
for j = 1:6 % Loop for eig(A).
    A = randn(matrix_size(j));
    % eig(A) warm-up and initialization.
    [V,D] = eig(A); sum = 0;
    for i = 1:20 % Counting 20 times.
        % Time calculation with tic-toc.
        tic; [V,D] = eig(A);
        sum = sum + toc; % Increasing sum.
    end
    rt_eig(j) = sum / 20; % Calcuating median.
end

figure; % Plotting the results.
plot(matrix_size,rt_lu,'b*-',...
     matrix_size,rt_qr,'r+-',...
     matrix_size,rt_svd,'gx-',...
     matrix_size,rt_eig,'cd-',...
     'LineWidth',2);
title('2-ii-b','fontWeight','bold');
xlabel('Matrix size n');
ylabel('Runtime (sec)');
legend('lu(A)','qr(A)','svd(A)','eig(A)',...
       'Location','NorthWest');
grid on;