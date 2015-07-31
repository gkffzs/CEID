function [E] = st_condrand_4465(n,kappa)

% Creating a random matrix.
X = rand(n);

% Calculating QR for the matrix.
[Q_X,R_X] = qr(X);

% Creating the diagonal matrix D.
K = zeros(n,1);
for i=1:n, K(i) = kappa^(-(i-1)/(n-1)); end
D = diag(K);

% Creating a symmetric matrix using Q_X and D.
A = Q_X*D*Q_X';

% Using the symmetric matrix with hess() in order to
% create a tridiagonal symmetric matrix with 
% condition number equal to kappa.
C = hess(A);

% Erasing the very small numbers above the three main diagonals.
E = diag(diag(C,-1),-1) + diag(diag(C)) + diag(diag(C,1),1);

% Printing out the calculated condition number.
fprintf('--- Final condition number: %d\n',cond(E));

end
