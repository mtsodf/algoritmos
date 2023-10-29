import pandas as pd

def construct_airports(df_group):
    # Build Airports

    airports ={} 
    id_to_airport = {}

    id = 0
    for row in df_group.iterrows():

        name = row[1]["Aeroporto.Origem"]
        if name not in airports:
            id_to_airport[id] = name
            airports[name] = {
                "name": name,
                "country": row[1]["Pais.Origem"],
                "city": row[1]["Cidade.Origem"],
                "lat": row[1]["LatOrig"],
                "lon": row[1]["LongOrig"],
                "id": id}
            id+=1
        name = row[1]["Aeroporto.Destino"]
        if name not in airports:
            airports[name] = {
                "name": name,
                "country": row[1]["Pais.Destino"],
                "city": row[1]["Cidade.Destino"],
                "lat": row[1]["LatDest"],
                "lon": row[1]["LongDest"], 
                "id": id}
            id+=1

    df_airports = pd.DataFrame.from_dict(airports, orient='index').reset_index()

    return df_airports, id_to_airport