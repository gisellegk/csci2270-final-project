subplot(2, 1, 1)
dataA = csvread('dataSetA.csv');
histogram(dataA)
title('dataSetA')

subplot(2, 1, 2)
dataC = csvread('dataSetC.csv');
histogram(dataC)
title('dataSetC')