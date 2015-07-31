function [] = script_2_2_i
% Variable initialization.
summary = 0; temp_sum = 0;
n = 1; run = true;
% Infinite loop til criterion's fulfilled.
while run
    % Temporary summary.
    temp_sum = summary + 1/n;
    % Criterion.
    if abs(temp_sum - summary) == 0
        run = false;
    end
    % Displaying current difference.
    disp(abs(temp_sum - summary))
    summary = temp_sum; % Current summary.
    n = n + 1; % Increment for next division.
end
