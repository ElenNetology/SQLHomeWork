-- количество исполнителей в каждом жанре;
SELECT list_of_musical_genres.name_genres, count(list_of_performers.name_performer) AS performer_in_genre FROM list_of_musical_genres
JOIN genres_performers ON list_of_musical_genres.id = genres_performers.id_genres 
JOIN list_of_performers ON genres_performers.id_performer = list_of_performers.id 
GROUP BY list_of_musical_genres.name_genres
ORDER BY count(id_performer) DESC;

-- количество треков, вошедших в альбомы 2019-2020 годов
SELECT albums_list.name_album AS albums_list, albums_list.year_of_release, count(track_list.name_track) AS tracks_in_albums FROM albums_list
JOIN track_list ON track_list.id_album = albums_list.id
GROUP BY albums_list.name_album, albums_list.year_of_release
HAVING albums_list.year_of_release BETWEEN '2019' AND '2020';

-- средняя продолжительность треков по каждому альбому
SELECT albums_list.name_album AS albums_list, avg(track_list.track_duration) AS average_songs_duration FROM albums_list
JOIN track_list ON track_list.id_album = albums_list.id 
GROUP BY albums_list.name_album
ORDER BY avg(track_list.track_duration);

-- все исполнители, которые не выпустили альбомы в 2020 году
SELECT DISTINCT list_of_performers.name_performer AS list_of_performers FROM list_of_performers
WHERE list_of_performers.name_performer NOT IN
(SELECT DISTINCT list_of_performers.name_performer AS list_of_performers FROM list_of_performers
JOIN albums_list ON album_performers.id_album = albums_list.id
JOIN album_performers ON list_of_performers.id = album_performers.id_performer 
WHERE albums_list.year_of_release = 2020)
ORDER BY list_of_performers.name_performer;

-- названия сборников, в которых присутствует конкретный исполнитель (выберите сами)
SELECT collection.name_collection AS collection, list_of_performers.name_performer AS list_of_performers FROM collection
LEFT JOIN tracks_collection ON collection.id = tracks_collection.id_collection 
LEFT JOIN track_list ON tracks_collection.id_track = track_list.id 
LEFT JOIN albums_list ON track_list.id_album = albums_list.id 
LEFT JOIN album_performers ON albums_list.id = album_performers.id_album 
LEFT JOIN list_of_performers ON album_performers.id_performer = list_of_performers.id
WHERE list_of_performers.id = 9
GROUP BY list_of_performers.name_performer, collection.name_collection;

-- название альбомов, в которых присутствуют исполнители более 1 жанра
SELECT albums_list.name_album AS albums_list FROM albums_list
LEFT JOIN album_performers ON albums_list.id = album_performers.id_album
LEFT JOIN list_of_performers ON list_of_performers.id = album_performers.id_performer 
LEFT JOIN genres_performers ON list_of_performers.id = genres_performers.id_performer 
LEFT JOIN list_of_musical_genres ON list_of_musical_genres.id = genres_performers.id_genres 
GROUP BY albums_list.name_album
HAVING count(distinct list_of_musical_genres.name_genres) > 1
ORDER BY albums_list.name_album;

-- наименование треков, которые не входят в сборники
SELECT track_list.name_track AS song FROM track_list
WHERE NOT EXISTS
(SELECT FROM tracks_collection WHERE tracks_collection.id_track  = track_list.id);

-- исполнителя(-ей), написавшего самый короткий по продолжительности трек (теоретически таких треков может быть несколько)
SELECT list_of_performers.name_performer AS list_of_performers, track_list.track_duration, track_list.name_track AS song FROM track_list
LEFT JOIN albums_list ON albums_list.id = track_list.id_album
LEFT JOIN album_performers ON album_performers.id_album = albums_list.id
LEFT JOIN list_of_performers ON list_of_performers.id = album_performers.id_performer
GROUP BY list_of_performers.name_performer, track_list.track_duration, track_list.name_track
HAVING track_list.track_duration = (SELECT min(track_duration) FROM track_list)
ORDER BY list_of_performers.name_performer; 

-- название альбомов, содержащих наименьшее количество треков
SELECT DISTINCT albums_list."name_album" AS albums_list FROM albums_list
JOIN track_list ON track_list.id_album = albums_list.id
WHERE track_list.id_album IN
(SELECT id_album FROM track_list
GROUP BY id_album
HAVING count (id_album) = (SELECT count(id_album) FROM track_list
GROUP BY id_album
ORDER BY count(id_album)
LIMIT 1))
ORDER BY albums_list."name_album";