function [c] = mv_ij(A,b)
% Vertical size of A matrix.
m = size(A,1);
% Initialization of c to store result.
c = zeros(m,1);
% Loop to perform the multiplication.
for i = 1:m
    c(i) = c(i) + A(i,:)*b;
end