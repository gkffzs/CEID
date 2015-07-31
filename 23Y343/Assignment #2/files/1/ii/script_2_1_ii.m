if (eps/2 == 0),
    disp(1)
end

if (1+eps > 1),
    disp(2)
end

if (1+realmin == 1),
    disp(3)
end

if (eps+realmax == realmax),
    disp(4)
end
