SELECT AVG(energy) AS avarage FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');