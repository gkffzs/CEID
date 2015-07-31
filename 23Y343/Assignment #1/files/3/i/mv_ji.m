function [c] = mv_ji(A,b)
% Vertical & horizontal size of A.
[m,n] = size(A);
% Initialization of c to store result.
c = zeros(m,1);
% Loop to perform the multiplication.
for j = 1:n
    c = c + A(:,j)*b(j);
end