% Creating a file to save results.
file_id = fopen('results_1_3.txt','w+');

% Loading initial signal.
[y,fs,N] = wavread('speech.wav');
% Quantization using PCM quantizer and 2 bits.
[xq,centers,p_e,D_e] = quantizer2_pcm(y,2,min(y),max(y));

% Printing out experimental results.
fprintf(file_id,'--------------------------------\n');
fprintf(file_id,'      EXPERIMENTAL RESULTS      \n');
fprintf(file_id,'--------------------------------\n');
fprintf(file_id,'Probabilities ------------------\n');
for i=1:4
    fprintf(file_id,'\t#%d level: %f\n',i,p_e(i));
end
fprintf(file_id,'Distortion: %f\n',D_e);

% Calculation of segment limits.
T = zeros(((2^2)+1),1); % Initialization.
T(1) = max(y); % Higher level limit.
for i=2:(2^2) % Middle levels.
    T(i) = (centers(i)+centers(i-1))/2;
end
T(5) = min(y); % Lower level limit.
% Specifying mu and sigma.
m = -0.04; s = sqrt(0.11);
% Initilization.
p_t = zeros((2^2),1);
for i=1:(2^2) % Calculating theoritical probabilities.
    p_t(i) = normcdf(T(i),m,s) - normcdf(T(i+1),m,s);
end
% Calculation of mean distortion.
syms y; D_t = 0; % Initialization.
for i=4:-1:1 % Calculation of integrals.
    f = ((y-centers(i))^2)*normpdf(y,m,s);
    D_t = D_t + double(int(f,T(i+1),T(i)));
end

% Printing out theoritical results.
fprintf(file_id,'--------------------------------\n');
fprintf(file_id,'       THEORITICAL RESULTS      \n');
fprintf(file_id,'--------------------------------\n');
fprintf(file_id,'Probabilities ------------------\n');
for i=1:4
    fprintf(file_id,'\t#%d level: %f\n',i,p_t(i));
end
fprintf(file_id,'Distortion: %f\n',D_t);

% Closing text file.
fclose(file_id);