% Loading initial signal.
[y,fs,N] = wavread('speech.wav');

% Quantization using PCM quantizer.
[xq4_pcm,centers4_pcm,p4_pcm,D4_pcm] = quantizer2_pcm(y,4,min(y),max(y));
[xq8_pcm,centers8_pcm,p8_pcm,D8_pcm] = quantizer2_pcm(y,8,min(y),max(y));
% Quantization using PCM with Lloyd-Max quantizer.
[xq4_lm,centers4_lm,p4_lm,D4_lm] = quantizer2_lm(y,4,min(y),max(y));
[xq8_lm,centers8_lm,p8_lm,D8_lm] = quantizer2_lm(y,8,min(y),max(y));
% Quantization using Huffman.
[~,len4_pcm] = huffman(p4_pcm);
[~,len8_pcm] = huffman(p8_pcm);
[~,len4_lm] = huffman(p4_lm);
[~,len8_lm] = huffman(p8_lm);

% Calculation of entropy.
temp_entr4_pcm = zeros(length(p4_pcm),1);
temp_entr8_pcm = zeros(length(p8_pcm),1);
temp_entr4_lm = zeros(length(p4_lm),1);
temp_entr8_lm = zeros(length(p8_lm),1);
for i=1:length(p4_pcm)
    if (p4_pcm(i) ~= 0)
        temp_entr4_pcm(i) = p4_pcm(i)*log2(1/p4_pcm(i));
    end
end
for i=1:length(p8_pcm)
    if (p8_pcm(i) ~= 0)
        temp_entr8_pcm(i) = p8_pcm(i)*log2(1/p8_pcm(i));
    end
end
for i=1:length(p4_lm)
    if (p4_lm(i) ~= 0)
        temp_entr4_lm(i) = p4_lm(i)*log2(1/p4_lm(i));
    end
end
for i=1:length(p8_lm)
    if (p8_lm(i) ~= 0)
        temp_entr8_lm(i) = p8_lm(i)*log2(1/p8_lm(i));
    end
end
entropy4_pcm = sum(temp_entr4_pcm);
entropy8_pcm = sum(temp_entr8_pcm);
entropy4_lm = sum(temp_entr4_lm);
entropy8_lm = sum(temp_entr8_lm);

% Calculation of mean code-word length.
len4_pcm = len4_pcm'; len8_pcm = len8_pcm';
len4_lm = len4_lm'; len8_lm = len8_lm';
L4_pcm = sum(len4_pcm.*p4_pcm);
L8_pcm = sum(len8_pcm.*p8_pcm);
L4_lm = sum(len4_lm.*p4_lm);
L8_lm = sum(len8_lm.*p8_lm);

% Calculation of efficiency.
efficiency4_pcm = entropy4_pcm/L4_pcm;
efficiency8_pcm = entropy8_pcm/L8_pcm;
efficiency4_lm = entropy4_lm/L4_lm;
efficiency8_lm = entropy8_pcm/L8_lm;

% Printing out results.
fprintf('----------------------------------\n');
fprintf('       HUFFMAN EFFICIENCIES       \n');
fprintf('----------------------------------\n');
fprintf('\tPCM (4 bits): %f\n',efficiency4_pcm);
fprintf('\tPCM (8 bits): %f\n',efficiency8_pcm);
fprintf('\tLM (4 bits): %f\n',efficiency4_lm);
fprintf('\tLM (8 bits): %f\n',efficiency8_lm);