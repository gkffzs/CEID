function [alphabet,probability,entropy] = function_1_6 % ----------------
% INPUT -----------------------------------------------------------------
%   (none)
% OUTPUT ----------------------------------------------------------------
%   alphabet: set of letters in source text
%   probability: probability of each alphabet symbol
%   entropy: measure of information in source text
% -----------------------------------------------------------------------

% Opening given text file.
file_id = fopen('keimeno.txt');
% Reading every character.
characters = fscanf(file_id,'%c');
% Closing text file handler.
fclose(file_id);
% Counting read characters.
number_of_chars = length(characters);
% Converting characters to ASCII.
ascii_chars = abs(characters);
% Initializing frequency and probability.
frequency = zeros(128,1);
% Calculation of every character's frequency.
for i=1:number_of_chars
    for n=1:128
        if (ascii_chars(i) == (n-1))
            frequency(n) = frequency(n) + 1;
        end
    end
end
% Calculation of probability.
temp_prob = frequency./number_of_chars;
% Finding nonzero values of probability.
pos_ind = find(temp_prob);
% Returning text's alphabet. (ASCII = pos-1)
alphabet = char(pos_ind-1);
% Returning probability for each letter of alphabet.
probability = temp_prob(pos_ind);
% Calculation of entropy.
temp_entr = zeros(length(pos_ind),1);
for i=1:length(pos_ind)
    temp_entr(i) = probability(i)*log2(1/probability(i));
end
% Returning text's entropy.
entropy = sum(temp_entr);
% Encoding text with Huffman.
[~,len] = huffman(probability);
% Reversing len for next calculation.
len = len';
% Calculating mean code-word length.
L = sum(len.*probability);
% Calculation of Huffman's efficiency.
efficiency = entropy/L;
% Printing out the result.
fprintf('Huffman efficiency: %f\n',efficiency);