% Specifying SNR values.
SNR = [0:2:30]; %#ok<NBRAK>

% Running our telecommunication system for each modulation.
[BER_i_2PAM,BER_n_2PAM] = script_2_b(SNR); % For 2-PAM.
[BER_i_4PAM,BER_n_4PAM] = script_2_c(SNR); % For 4-PAM.
[BER_i_4QAM,BER_n_4QAM] = script_2_d(SNR); % For 4-QAM.

% Plotting the results as BER/SNR on one figure.
figure;
semilogy(SNR,BER_i_2PAM,'-g','LineWidth',2); hold on;
semilogy(SNR,BER_n_2PAM,':g','LineWidth',2); hold on;
semilogy(SNR,BER_i_4PAM,'-b','LineWidth',2); hold on;
semilogy(SNR,BER_n_4PAM,':b','LineWidth',2); hold on;
semilogy(SNR,BER_i_4QAM,'-m','LineWidth',2); hold on;
semilogy(SNR,BER_n_4QAM,':m','LineWidth',2); hold off;
legend('2-PAM (i)','2-PAM (n)',...
       '4-PAM (i)','4-PAM (n)',...
       '4-QAM (i)','4-QAM (n)',...
       'Location','Best');
xlabel('Signal-to-Noise Ratio (SNR)');
ylabel('Bit Error Ratio (BER)');
title('Comparative Figure For All Modulations');

% Creating a file to save the results.
file_id = fopen('results_2_e.txt','w+');
% Saving results for 2-PAM modulation.
fprintf(file_id,'----------------------------------------------\n');
fprintf(file_id,'|||||||||||||||||||||||||||||||||||| 2-PAM |||\n');
fprintf(file_id,'BER (ideal channel) --------------------------\n');
for i=1:length(BER_i_2PAM)
    fprintf(file_id,'   [%d] %f\n',SNR(i),BER_i_2PAM(i));
end
fprintf(file_id,'BER (non-ideal channel) ----------------------\n');
for i=1:length(BER_n_2PAM)
    fprintf(file_id,'   [%d] %f\n',SNR(i),BER_n_2PAM(i));
end
% Saving results for 4-PAM modulation.
fprintf(file_id,'----------------------------------------------\n');
fprintf(file_id,'|||||||||||||||||||||||||||||||||||| 4-PAM |||\n');
fprintf(file_id,'BER (ideal channel) --------------------------\n');
for i=1:length(BER_i_4PAM)
    fprintf(file_id,'   [%d] %f\n',SNR(i),BER_i_4PAM(i));
end
fprintf(file_id,'BER (non-ideal channel) ----------------------\n');
for i=1:length(BER_n_4PAM)
    fprintf(file_id,'   [%d] %f\n',SNR(i),BER_n_4PAM(i));
end
% Saving results for 4-QAM modulation.
fprintf(file_id,'----------------------------------------------\n');
fprintf(file_id,'|||||||||||||||||||||||||||||||||||| 4-QAM |||\n');
fprintf(file_id,'BER (ideal channel) --------------------------\n');
for i=1:length(BER_i_4QAM)
    fprintf(file_id,'   [%d] %f\n',SNR(i),BER_i_4QAM(i));
end
fprintf(file_id,'BER (non-ideal channel) ----------------------\n');
for i=1:length(BER_n_4QAM)
    fprintf(file_id,'   [%d] %f\n',SNR(i),BER_n_4QAM(i));
end

% Closing text file.
fclose(file_id);