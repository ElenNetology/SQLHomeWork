INSERT INTO tracks_collection (id_track, id_collection)
VALUES
(1,1);

INSERT INTO tracks_collection (id_track, id_collection)
VALUES
(generate_series(2, 10),generate_series(2, 10));

INSERT INTO tracks_collection (id_track, id_collection)
VALUES
(generate_series(11, 20),generate_series(1, 10));

INSERT INTO genres_performers (id_genres, id_performer)
VALUES
(generate_series(1, 10),generate_series(1, 10));

INSERT INTO genres_performers (id_genres, id_performer)
VALUES
(generate_series(3, 6),generate_series(7, 10));

-- Генерация album + performer: 
-- a). Альбом могут выпустить несколько исполнителей вместе. 
-- б). Исполнитель может принимать участие во множестве альбомов.
INSERT INTO album_perfomers (id_performer, id_album)
VALUES
(generate_series(1, 10),generate_series(1, 10));

INSERT INTO album_perfomers (id_performer, id_album)
VALUES
(generate_series(2, 5),generate_series(6, 9));