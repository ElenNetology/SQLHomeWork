-- название и год выхода альбомов, вышедших в 2018 году
SELECT name_album, year_of_release FROM albums_list WHERE year_of_release = '2018';

-- название и продолжительность самого длительного трека
SELECT name_track, track_duration FROM track_list WHERE track_duration = (SELECT max(track_duration) FROM track_duraition);

-- название треков, продолжительность которых не менее 3,5 минуты
SELECT name_track FROM track_list WHERE track_duration >= '00:03:30';

-- название треков, продолжительность которых не менее 3 часов и 3,5 минут
SELECT name_track FROM track_list WHERE track_duration >= '03:03:30';

-- названия сборников, вышедших в период с 2018 по 2020 год включительно
SELECT name_collection, year_of_release FROM collection WHERE year_of_release BETWEEN '2018' AND '2020';

-- исполнители, чье имя состоит из 1 слова
SELECT name_performer FROM list_of_performers WHERE name_performer NOT LIKE '%% %%';

-- название треков, которые содержат слово “мой”/“my”
SELECT name_track FROM track_list WHERE name_track iLIKE '%my%';