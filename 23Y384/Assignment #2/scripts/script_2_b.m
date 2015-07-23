function [BER_i,BER_n] = script_2_b(SNR) % --------------------------------
% INPUT -------------------------------------------------------------------
%   SNR: desired signal-to-noise ratios
% OUTPUT ------------------------------------------------------------------
%   BER_i: bit error rate for the ideal channel
%   BER_n: bit error rate for the non-ideal channel
% -------------------------------------------------------------------------

% Printing intro.
fprintf('||||||||||| 2-PAM Modulation |||||||||||\n');
fprintf('----------------------------------------\n');

% Calculating number of different SNR values.
SNR_length = length(SNR);
% Specifying 2-PAM's alphabet.
s = [-1 1];
% Number of data to be used.
data_number = 10^5;
% Generating a random input signal of symbols with equal probability.
input_signal = randsrc(data_number,1,s);
% Calculating the length of the generated signal.
i_s_length = length(input_signal);

% Printing out input signal's length for testing.
fprintf('Input signal length: %d\n',i_s_length);
fprintf('----------------------------------------\n');

% Initializing vectors to save the results.
output_signal_i = zeros(i_s_length,SNR_length);
output_signal_n = zeros(i_s_length,SNR_length);
% Running the system for 2-PAM modulation.
for j=1:SNR_length
    fprintf('|||> SNR|db = %d\n',SNR(j));
    fprintf('---- [i]\n');
    output_signal_i(:,j) = script_2_a(input_signal,s,'i',SNR(j));
    fprintf('---- [n]\n');
    output_signal_n(:,j) = script_2_a(input_signal,s,'n',SNR(j));
    fprintf('\n');
end
fprintf('----------------------------------------\n');

% Converting signals to binary represantation, in order to calculate BER.
% Initializing a vector to save the results.
binary_input = zeros(i_s_length,1);
% We need 1 bit per symbol, and so we assign '0' to -1 and '1' to 1.
for i=1:i_s_length
    % Converting only the negative values of input signal to zero.
    if(input_signal(i) == -1)
        binary_input(i) = 0;
    elseif(input_signal(i) == 1)
        binary_input(i) = 1;
    end
end

% Initializing vectors to save the results.
binary_output_i = zeros(i_s_length,SNR_length);
binary_output_n = zeros(i_s_length,SNR_length);
% Converting the 2 output signals for each case respectively.
for j=1:SNR_length
    for i=1:i_s_length
        % Converting output signal for ideal channel.
        if(output_signal_i(i,j) == -1)
            binary_output_i(i,j) = 0;
        elseif(output_signal_i(i,j) == 1)
            binary_output_i(i,j) = 1;
        end
        % Converting output signal for non-ideal channel.
        if(output_signal_n(i,j) == -1)
            binary_output_n(i,j) = 0;
        elseif(output_signal_n(i,j) == 1)
            binary_output_n(i,j) = 1;
        end   
    end
end

% Calculating the bit error ratios (BER) for each case of SNR value.
n_i = zeros(SNR_length,1); BER_i = zeros(SNR_length,1);
n_n = zeros(SNR_length,1); BER_n = zeros(SNR_length,1);
for j=1:SNR_length
    [n_i(j),BER_i(j)] = biterr(binary_output_i(:,j),binary_input);
    [n_n(j),BER_n(j)] = biterr(binary_output_n(:,j),binary_input);
end

% Plotting the results as BER/SNR on one figure.
figure;
semilogy(SNR,BER_i,'-g','LineWidth',2); hold on;
semilogy(SNR,BER_n,':g','LineWidth',2); hold off;
legend('ideal','non-ideal','Location','Best');
xlabel('Signal-to-Noise Ratio (SNR)');
ylabel('Bit Error Ratio (BER)');
title('2-PAM Modulation'); 

end