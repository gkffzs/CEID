function [xq,centers,p,D] = quantizer2_lm(x,N,min_value,max_value) % ----
% INPUT -----------------------------------------------------------------
%   x: vector of input signal
%   N: number of bits to be used
%   min_value: minimum acceptable value of input signal
%   max_value: maximum acceptable value of input signal
% OUTPUT ----------------------------------------------------------------
%   xq: encoded vector of output signal
%   centers: centers of quantization segments
%   p: probability of each symbol
%   D: vector of signal's distortion at every repetition  
% -----------------------------------------------------------------------

% Number of bits used.
v = N;
% Levels of quantization.
quant_levels = 2^v;
% Initialization of vector xq.
xq = zeros(length(x),1);
% Quantization step Ä.
quant_step = (abs(min_value)+max_value)/quant_levels;
% Calculation of centers.
centers = zeros(quant_levels,1); % Initialization.
for i=1:quant_levels
    centers(i) = max_value-(2*(i-1)+1)*(quant_step/2);
end
% Loop for Lloyd-Max algorithm.
T = zeros((quant_levels+1),1); % Initialization of segments' limits.
counter = 1; % Initialization of iterations' counter.
previous_distortion = 0; % Initialization of previous distortion.
while 1
    % [1] Calculation of new segments' limits.
    T(1) = max_value; % Higher level limit.
    for i=2:quant_levels % Middle levels.
        T(i) = (centers(i)+centers(i-1))/2;
    end
    T(quant_levels+1) = min_value; % Lower level limit.
    
    % [2] Calculation of output signal & distortion.
    q_max_value = 1; q_min_value = quant_levels;
    for i=1:length(x)
        % If x(i) is greater or equal to max_value.
        if (x(i) >= max_value)
            xq(i) = q_max_value;
        % If x(i) is smaller than min_value.
        elseif (x(i) <= min_value)
            xq(i) = q_min_value;
        else % For every other case inbetween.
            for n=1:quant_levels
                if ((x(i) <= T(n)) && (x(i) > T(n+1)))
                    xq(i) = n;
                end
            end
        end
    end
    % Check if there are any zeros.
    if (all(xq)) % If not, calculate the distortion.
        D(counter) = mean((x-centers(xq)).^2); %#ok<AGROW>
    else % If yes, print out an error message.
        fprintf('Error: there are zeros as index.\n');
    end
    
    % [4] Criterion check. If fulfilled, stop the loop.
    difference = abs(D(counter)-previous_distortion);
    if (difference < eps('single'))
        break;
    else % Else, store current distortion for the next comparison.
        previous_distortion = D(counter);
    end
    
    % [3] New levels of quantization.
    temp_sum = zeros(quant_levels,1); % Temporary summary.
    temp_counter = zeros(quant_levels,1); % Number of values in each level.
    for n=1:quant_levels
        for i=1:length(x)
            % Check if x(i) belongs to n level.
            if (x(i) <= T(n) && x(i) > T(n+1))
                temp_sum(n) = temp_sum(n) + x(i);
                temp_counter(n) = temp_counter(n) + 1;
            % If x(i) is greater than max_value.
            elseif ((x(i) > T(n)) && (n == 1))
                temp_sum(n) = temp_sum(n) + T(n);
                temp_counter(n) = temp_counter(n) + 1;
            % If x(i) is smaller than min_value.
            elseif ((x(i) < T(n+1)) && (n == quant_levels))
                temp_sum(n) = temp_sum(n) + T(n+1);
                temp_counter(n) = temp_counter(n) + 1;
            end
        end
        % Calculating the new center for n level.
        if (temp_counter(n) > 0) % If greater than zero, calculate.
            centers(n) = temp_sum(n)/temp_counter(n);
        end;
    end
    
    % Increment of iteration counter.
    counter = counter + 1;
end
% Calculating probabilities.
frequency = zeros(quant_levels,1);
for i=1:quant_levels
    for k=1:length(xq)
        if (i == xq(k))
            frequency(i) = frequency(i) + 1;
        end
    end
end
p = frequency./length(xq);
% Printing out the final number of iterations.
fprintf('(%d bits) Kmax = %d\n',N,counter);