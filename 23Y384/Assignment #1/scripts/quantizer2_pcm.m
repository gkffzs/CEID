function [xq,centers,p,D] = quantizer2_pcm(x,N,min_value,max_value) % ---
% INPUT -----------------------------------------------------------------
%   x: vector of input signal
%   N: number of bits to be used
%   min_value: minimum acceptable value of input signal
%   max_value: maximum acceptable value of input signal
% OUTPUT ----------------------------------------------------------------
%   xq: vector of output signal
%   centers: centers of quantization segments
%   p: probability of each symbol
%   D: distortion after encoding
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
% Initialization for frequency counter.
frequency = zeros(quant_levels,1);
% Calculation of output signal. (quantization)
q_max_value = 1; q_min_value = quant_levels;
for i=1:length(x)
    % If x(i) is greater or equal to max_value.
    if (x(i) >= max_value)
        xq(i) = q_max_value;
        frequency(1) = frequency(1) + 1;
    % If x(i) is smaller than min_value.
    elseif (x(i) < min_value)
        xq(i) = q_min_value;
        frequency(quant_levels) = frequency(quant_levels) + 1;
    else % For every other case in-between.
        for n=1:quant_levels
            if (x(i) >= (centers(n)-(quant_step/2)) && ...
                x(i) < (centers(n)+(quant_step/2)))
                xq(i) = n;
                frequency(n) = frequency(n) + 1;
            end
        end
    end
end
% Calculation of probability for each level.
p = frequency./length(x);
% Calculation of distortion.
D = mean((x-centers(xq)).^2);