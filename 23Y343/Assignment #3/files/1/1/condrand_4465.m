function [A] = condrand_4465(n,kappa)

% Creating 2 random matrices.
X = rand(n);
Y = rand(n);

% Calculating QR for the matrices.
[Q_X,R_X] = qr(X);
[Q_Y,R_Y] = qr(Y);

% Creating the diagonal matrix D.
K = zeros(n,1);
for i=1:n, K(i) = kappa^(-(i-1)/(n-1)); end
D = diag(K);

% Final matrix with same condition number kappa.
A = Q_X*D*Q_Y;

% Display given and calculated condition number.
fprintf('CONDITION NUMBERS\n');
fprintf('--- As input: %d\n',kappa);
fprintf('--- As result: %d\n',cond(A));

end
