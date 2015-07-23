function [output] = script_2_a(input,s,channel,SNR) % ---------------------
% INPUT -------------------------------------------------------------------
%   input: input signal
%   s: source's alphabet
%   channel: type of the channel ('i' for ideal - 'n' for non-ideal)
%   SNR: signal to noise ratio (in dB)
% OUTPUT ------------------------------------------------------------------
%   output: output signal
% -------------------------------------------------------------------------

% -------------------------------------------------------[Upsampling input]
% Upsampling rate.
up_rate = 4;
% Upsampling the input signal.
upsampled_signal = upsample(input,up_rate);
% Calculating the length of the new signal.
u_s_length = length(upsampled_signal);
% Removing the last three zeros.
upsampled_signal = upsampled_signal(1:(u_s_length-(up_rate-1)));
% Printing out upsampled signal's length.
fprintf('Upsampled signal length: %d\n',length(upsampled_signal));

% --------------------------------------------------[Filter in transmitter]
% Specifying the input signal sampling period T_s (in seconds).
Ts = 1;
% Specifying number of sampling periods.
M = 6;
% Calculating total period.
T = M*Ts;
% Specifying the roll-off factor.
roll_off = 0.3;
% Creating transmitter's raised cosine FIR filter.
transmitter_filter = rcosfir(roll_off,[-T/2,T/2],up_rate,Ts,'sqrt');
% Calculating the signal with respect to the filter.
transmitted_signal = conv(transmitter_filter,upsampled_signal);
% Printing out transmitted signal's length.
fprintf('Transmitted signal length: %d\n',length(transmitted_signal));

% ------------------------------------------------------[Filter in channel]
% Impulse response of the non-ideal channel.
h = [0.01 0.04 -0.05 0.06 -0.22 -0.5 0.72 0.36 0 0.21 0.04 0.08 0.02];
% Upsampling the non-ideal channel's response.
upsampled_h = upsample(h,up_rate);
% Calculating the length of the upsampled response.
u_h_length = length(upsampled_h);
% Removing the last three zeros.
upsampled_h = upsampled_h(1:(u_h_length-(up_rate-1)));
% Specifying the type of the channel.
% If the channel is ideal, the transmitted signal passes.
if (channel == 'i'), channeled_signal = transmitted_signal;
% If it's non-ideal, the convolution of impulse and signal passes.
elseif (channel == 'n')
    channeled_signal = conv(upsampled_h,transmitted_signal);
end
% Printing out channeled signal's length.
fprintf('Channeled signal length: %d\n',length(channeled_signal));

% -------------------------------------------[Calculating noise in channel]
% Calculating the length of the channeled signal.
c_s_length = length(channeled_signal);
% Calculating the average power of the signal.
Ps = sum(abs(channeled_signal).^2)/c_s_length;
% Calculating the average power of the noise.
Pn = Ps/(10^(SNR/10));
% Noise's average power is equal to squared noise standard deviation.
sigma = sqrt(Pn);
% Creating noise randomly.
if(isreal(channeled_signal) == 1) % For real numbers.
    random_noise = randn(c_s_length,1);
else % For complex numbers.
    random_noise = (randn(c_s_length,1) + 1j*randn(c_s_length,1))/sqrt(2);
end
% Calculating the final channel noise.
channel_noise = sigma * random_noise;
% Adding noise to the signal.
signal_with_noise = channeled_signal + channel_noise;
% Printing out signal's length with noise.
fprintf('Signal with noise length: %d\n',length(signal_with_noise));

% -----------------------------------------------------[Filter in receiver]
% Filter in receiver is the same as in transmitter.
receiver_filter = transmitter_filter;
% Calculating the incoming signal with respect to the filter.
received_signal = conv(receiver_filter,signal_with_noise);
% Printing out received signal's length.
fprintf('Received signal length: %d\n',length(received_signal));

% ----------------------------------------------------[Downsampling signal]
% Calculating the filter's taps.
N = length(transmitter_filter);
% Calculating non-ideal channel's taps.
N_n = length(upsampled_h);
% Calculating the delay of the signal.
if (channel == 'i') % For ideal channel.
    delay = 2*(((N-1)*Ts)/2);
elseif (channel == 'n') % For non-ideal channel.
    delay = 2*(((N-1)*Ts)/2) + (((N_n-1)*Ts)/2);
end
fprintf('Delay: %d\n',delay);
% Removing delay from our signal.
temp_signal = received_signal(delay+1:(end-delay));
% Downsampling received signal with respect to delay.
downsampled_signal = downsample(temp_signal,up_rate);
% Printing out downsampled signal's length.
fprintf('Downsampled signal length: %d\n',length(downsampled_signal));

% -------------------------------------------------------[Decision process]
% Calculating the length of the downsampled signal.
d_s_length = length(downsampled_signal);
% Initializing the output signal vector.
output = zeros(d_s_length,1);
% Calculating the length of the alphabet.
s_length = length(s);
% Initializing th D vector of distance metrics.
D = zeros(s_length,1);
% Finding the minimum distance of each signal's value from the symbols.
for i=1:d_s_length
    % Calculating the squared distance.
    for j=1:s_length
        D(j) = (downsampled_signal(i) - s(j))^2;
    end
    % Sorting D vector with ascending order, minimum distance is on top.
    [D,I] = sort(D,'ascend');
    % Returning the symbol with the smallest Euclidean distance.
    output(i) = s(I(1));
end

end