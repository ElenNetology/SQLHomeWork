CREATE TABLE IF NOT EXISTS list_of_musical_genres (
id SERIAL PRIMARY KEY NOT NULL,
name_genres VARCHAR(60) NOT NULL
);

CREATE TABLE IF NOT EXISTS albums_list (
id SERIAL PRIMARY KEY NOT NULL,
name_album VARCHAR(60) NOT NULL,
year_of_release INTEGER
);

CREATE TABLE IF NOT EXISTS list_of_performers (
id SERIAL PRIMARY KEY NOT NULL,
name_performer VARCHAR(60) NOT NULL
);

CREATE TABLE IF NOT EXISTS collection (
id SERIAL PRIMARY KEY NOT NULL,
name_collection VARCHAR(60) NOT NULL,
year_of_release INTEGER
);

CREATE TABLE IF NOT EXISTS track_list (
id SERIAL PRIMARY KEY NOT NULL,
name_track VARCHAR(60) NOT NULL,
id_album INTEGER REFERENCES albums_list(id),
track_duration INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS tracks_collection (
id_track INTEGER REFERENCES track_list(id),
id_collection INTEGER REFERENCES collection(id),
CONSTRAINT pk_tracks_collection PRIMARY KEY (id_track, id_collection)
);

CREATE TABLE genres_performers (
id_genres INTEGER REFERENCES list_of_musical_genres(id),
id_performer INTEGER REFERENCES list_of_performers(id),
CONSTRAINT genres_singer_pkey PRIMARY KEY (id_genres, id_performer) -- связь между жанрами и исполнителями
);

CREATE TABLE album_perfomers (
id_performer INTEGER REFERENCES list_of_performers(id),
id_album INTEGER REFERENCES albums_list(id),
CONSTRAINT pk_singer_album PRIMARY KEY (id_performer, id_album) -- связь между исполнителями и альбомами
);