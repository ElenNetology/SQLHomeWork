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

