import pandas as pd
import numpy as np
import xgboost as xgb


def predict_val(future_with_features):
    reg_loaded = xgb.XGBRegressor()
    reg_loaded.load_model('model.json')
    future_with_features['pred'] = reg_loaded.predict(future_with_features[['dayofyear', 'hour', 'dayofweek', 'quarter', 'month','year',
                'lag1','lag2','lag3']])

    return future_with_features

def loadFutureDF(last_date,future_last_date,df):
    future = pd.date_range('last_date','future_last_date', freq='1h')
    future_df = pd.DataFrame(index=future)
    future_df['isFuture'] = True
    df['isFuture'] = False
    df_and_future = pd.concat([df, future_df])
    df_and_future = create_features(df_and_future)
    df_and_future = add_lags(df_and_future)
    future_with_features = df_and_future.query('isFuture').copy()
    return future_with_features
    
    

def loadDF():
    df = pd.read_csv('AEP_hourly.csv\AEP_hourly.csv')
    df = df.set_index('Datetime')
    df.index = pd.to_datetime(df.index)
    df = create_features(df)
    add_lags(df)
    return df

###creating features 
def create_features(df):
    df['hour'] = df.index.hour
    df['dayofweek'] = df.index.dayofweek
    df['quarter'] = df.index.quarter
    df['month'] = df.index.month
    df['year'] = df.index.year
    df['dayofyear'] = df.index.dayofyear
    df['dayofmonth'] = df.index.day
    df['weekofyear'] = df.index.isocalendar().week
    return df



###adding lag functions 
def add_lags(df):
    # Convert the 'Datetime' column to a datetime index
    # df['Datetime'] = pd.to_datetime(df['Datetime'])
    # df.set_index('Datetime', inplace=True)

    # Specify the date offsets for the lags
    date_offsets = [+5460, +5824, +6188]  # Days

    # Create lag features using shift
    for lag, offset in enumerate(date_offsets, start=1):
        df[f'lag{lag}'] = df['AEP_MW'].shift(periods=offset)
    return df
