function [code,len]=huffman(p);
% Huffman Coding.
%	 	[code,len]=huffman(p), 
%	 	INPUTS
%       p(vector): contains the probabilities of each symbol
%       OUTPUTS
%       code(vector): the code for each symbol (in ascii format)
%       len(vector): the number of bits needed for each code

p = p(:)';

if length(find(p<0))~=0,  
    error('Not a probability vector, negative component(s)')
end;

if abs(sum(p)-1)>10e-10,  
    error('Not a probability vector, components do not add up to 1')
end;
n=length(p);
q=p;
m=zeros(n-1,n);

for i=1:n-1,
    [q,l]=sort(q); 
    m(i,:)=[l(1:n-i+1),zeros(1,i-1)]; 
    q=[q(1)+q(2),q(3:n),1];
end;

for i=1:n-1,
    c(i,:)=blanks(n*n);
end;

c(n-1,n)='0';
c(n-1,2*n)='1';

for i=2:n-1, 
    c(n-i,1:n-1)=c(n-i+1,n*(find(m(n-i+1,:)==1))-(n-2):n*(find(m(n-i+1,:)==1)));
    c(n-i,n)='0'; 
    c(n-i,n+1:2*n-1)=c(n-i,1:n-1);
    c(n-i,2*n)='1';
    for j=1:i-1,
        c(n-i,(j+1)*n+1:(j+2)*n)=c(n-i+1,...  
            n*(find(m(n-i+1,:)==j+1)-1)+1:n*find(m(n-i+1,:)==j+1));  
    end;
end;

for i=1:n,
    code(i,1:n)=c(1,n*(find(m(1,:)==i)-1)+1:find(m(1,:)==i)*n); 
    len(i)=length(find(abs(code(i,:))~=32));
end;