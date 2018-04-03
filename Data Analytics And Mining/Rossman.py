#Standrad
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
get_ipython().magic('matplotlib inline')

import xgboost as xgb
from xgboost import plot_importance
from sklearn import cross_validation

#CV
from sklearn.cross_validation import *
from sklearn.grid_search import GridSearchCV


#Import Data
trainDF = pd.read_csv('Data\\train.csv')
testDF = pd.read_csv('Data\\test.csv')
storeDF = pd.read_csv('Data\\store.csv')


#Define ID Column & Target
targetCol = 'Sales'

print("Reclassify all data to int or float for Linear Regression ")
#Reclassify all data to int or float for Linear Regression 
#0, a, b, c, d map to 0, 1, 2, 3, 4
abcdmappings = {'0':0, 'a':1, 'b':2, 'c':3, 'd':4}
storeDF.StoreType.replace(abcdmappings, inplace = True)
storeDF.Assortment.replace(abcdmappings, inplace = True)

#Split Date to Year, Month, Day, DayOfWeek, WeekOfYear
trainDF['Date'] = pd.to_datetime(trainDF['Date'], errors='coerce')
trainDF['Month'] = trainDF.Date.dt.month
trainDF['Day'] = trainDF.Date.dt.day
trainDF['DayOfWeek'] = trainDF.Date.dt.dayofweek
trainDF.drop('Date', axis=1, inplace=True)

testDF['Date'] = pd.to_datetime(testDF['Date'], errors='coerce')
testDF['Month'] = testDF.Date.dt.month
testDF['Day'] = testDF.Date.dt.day
testDF['DayOfWeek'] = testDF.Date.dt.dayofweek
testDF.drop('Date', axis=1, inplace=True)


#Drop Promotion Interval for now as it is hard to process
storeDF.drop('PromoInterval', axis=1, inplace=True)

trainDF.drop('Customers', axis=1, inplace=True)

#Only consider Opened sotre & Drop Open Column
trainDF = trainDF[trainDF["Open"] != 0]
trainDF.drop('Open', axis=1, inplace=True)

#Droppiing Unwanted row
trainDF.drop('StateHoliday', axis=1, inplace=True)
testDF.drop('StateHoliday', axis=1, inplace=True)
storeDF.drop('Promo2', axis=1, inplace=True)


#Train DataType Clean Up
trainDF['Promo'] = trainDF['Promo'].astype('bool')
trainDF['SchoolHoliday'] = trainDF['SchoolHoliday'].astype('bool')

#Test Data Clean Up
#Setting Nan value in Open to 1
testDF['Promo'] = testDF['Promo'].astype('bool')
testDF['SchoolHoliday'] = testDF['SchoolHoliday'].astype('bool')

#Fill all Nan to 0
trainDF=trainDF.fillna(0)


#Merge with Strore
trainDF = pd.merge(trainDF, storeDF, on='Store')
testDF = pd.merge(testDF, storeDF, on='Store')


#Evaluation function for XGB
def ToWeight(y):
    w = np.zeros(y.shape, dtype=float)
    ind = y != 0
    w[ind] = 1./(y[ind]**2)
    return w

def rmspe(yhat, y):
    w = ToWeight(y)
    rmspe = np.sqrt(np.mean( w * (y - yhat)**2 ))
    return rmspe


def rmspe_xg(yhat, y):
    y = y.get_label()
    y = np.exp(y) - 1
    yhat = np.exp(yhat) - 1
    w = ToWeight(y)
    rmspe = np.sqrt(np.mean(w * (y - yhat)**2))
    return "rmspe", rmspe

print("Splitting data to 90% train, 9% test and 1% valid")
#Split data to 90% train, 9% test and 1% valid
Train, Test = cross_validation.train_test_split(trainDF, test_size=0.1)
Test, Valid = cross_validation.train_test_split(Test, test_size=0.1)


print("Training")
#XGB Params
params = {"objective": "reg:linear",
          "eta": 0.3,
          "max_depth": 10,
          "subsample": 0.7,
          "colsample_bytree": 0.7,
          "silent": 1
          }
#Number of max iteration
num_trees = 300

#XGB Matrix
dtrain = xgb.DMatrix(Train[[x for x in Train.columns if x not in [targetCol]]], np.log(Train[targetCol] + 1))
dvalid = xgb.DMatrix(Test[[x for x in Test.columns if x not in [targetCol]]], np.log(Test[targetCol] + 1))

#Watchlist for the evaluation function declared
watchlist = [(dvalid, 'eval'), (dtrain, 'train')]

#Start XGB traing
gbm = xgb.train(params, dtrain, num_trees, evals=watchlist, early_stopping_rounds=50, feval=rmspe_xg, verbose_eval=True)


#Validating the traiing model with the 1% of valid data
print("Validating")
train_probs = gbm.predict(xgb.DMatrix(Valid[[x for x in trainDF.columns if x not in [targetCol]]]))
indices = train_probs < 0
train_probs[indices] = 0
error = rmspe(np.exp(train_probs) - 1, Valid[targetCol].values)
print('error', error)


#Using XGB.predict to precict the future.
test_probs = gbm.predict(xgb.DMatrix(testDF[[x for x in trainDF.columns if x not in [targetCol]]]))
#If sales is less than 0, set to 0
indices = test_probs < 0
test_probs[indices] = 0
submission = pd.DataFrame({"Id": testDF["Id"], "Sales": np.exp(test_probs) - 1})
submission.to_csv("CHONGJIAYI_Rossman.csv", index=False)


#plot importance for presentation
plot_importance(gbm)
plt.show




