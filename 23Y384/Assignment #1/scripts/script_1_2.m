% Loading initial signal.
[y,fs,N] = wavread('speech.wav');

% Quantization using 2,4 and 8 bits for both quantizers.
[xq2_pcm,centers2_pcm] = my_quantizer(y,2,min(y),max(y));
[xq4_pcm,centers4_pcm] = my_quantizer(y,4,min(y),max(y));
[xq8_pcm,centers8_pcm] = my_quantizer(y,8,min(y),max(y));
[xq2_lm,centers2_lm,D2_lm] = Lloyd_Max(y,2,min(y),max(y));
[xq4_lm,centers4_lm,D4_lm] = Lloyd_Max(y,4,min(y),max(y));
[xq8_lm,centers8_lm,D8_lm] = Lloyd_Max(y,8,min(y),max(y));

% Calculating SQNR for PCM and plotting it for Lloyd-Max.
SQNR2_pcm = mean(y.^2)/mean((y-centers2_pcm(xq2_pcm)).^2);
fprintf('SQNR2_pcm: %f\n',SQNR2_pcm);
SQNR4_pcm = mean(y.^2)/mean((y-centers4_pcm(xq4_pcm)).^2);
fprintf('SQNR4_pcm: %f\n',SQNR4_pcm);
SQNR8_pcm = mean(y.^2)/mean((y-centers8_pcm(xq8_pcm)).^2);
fprintf('SQNR8_pcm: %f\n',SQNR8_pcm);
SQNR2_lm = mean(y.^2)./D2_lm;
figure; plot(SQNR2_lm,'g','LineWidth',2); title('SQNR (N=2, Lloyd-Max)');
xlabel('Iterations'); ylabel('SQNR'); grid on;
SQNR4_lm = mean(y.^2)./D4_lm;
figure; plot(SQNR4_lm,'g','LineWidth',2); title('SQNR (N=4, Lloyd-Max)');
xlabel('Iterations'); ylabel('SQNR'); grid on;
SQNR8_lm = mean(y.^2)./D8_lm;
figure; plot(SQNR8_lm,'g','LineWidth',2); title('SQNR (N=8, Lloyd-Max)');
xlabel('Iterations'); ylabel('SQNR'); grid on;

% Saving audio objects for each quantization case.
initial_track = audioplayer(y,fs);
track2_pcm = audioplayer(centers2_pcm(xq2_pcm),fs);
track4_pcm = audioplayer(centers4_pcm(xq4_pcm),fs);
track8_pcm = audioplayer(centers8_pcm(xq8_pcm),fs);
track2_lm = audioplayer(centers2_lm(xq2_lm),fs);
track4_lm = audioplayer(centers4_lm(xq4_lm),fs);
track8_lm = audioplayer(centers8_lm(xq8_lm),fs);

% Plotting all signals.
figure; plot(y,'g','LineWidth',2); title('Initial signal'); grid on;
figure; plot(centers2_pcm(xq2_pcm),'g','LineWidth',2);
title('Signal (N=2, PCM)'); grid on;
figure; plot(centers4_pcm(xq4_pcm),'g','LineWidth',2);
title('Signal (N=4, PCM)'); grid on;
figure; plot(centers8_pcm(xq8_pcm),'g','LineWidth',2);
title('Signal (N=8, PCM)'); grid on;
figure; plot(centers2_lm(xq2_lm),'g','LineWidth',2);
title('Signal (N=2, Lloyd-Max)'); grid on;
figure; plot(centers4_lm(xq4_lm),'g','LineWidth',2);
title('Signal (N=4, Lloyd-Max)'); grid on;
figure; plot(centers8_lm(xq8_lm),'g','LineWidth',2);
title('Signal (N=8, Lloyd-Max)'); grid on;