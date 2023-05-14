CREATE TABLE IF NOT EXISTS List_of_musical_genres (
id SERIAL PRIMARY KEY NOT NULL,
Name_genres VARCHAR(60) NOT NULL
);

CREATE TABLE IF NOT EXISTS Albums_list (
id SERIAL PRIMARY KEY NOT NULL,
Name_album VARCHAR(60) NOT NULL,
Year_of_release INTEGER
);

CREATE TABLE IF NOT EXISTS List_of_performers (
id SERIAL PRIMARY KEY NOT NULL,
Name_performer VARCHAR(60) NOT NULL
);

CREATE TABLE IF NOT EXISTS Collection (
id SERIAL PRIMARY KEY NOT NULL,
Name_collection VARCHAR(60) NOT NULL,
Year_of_release INTEGER
);

CREATE TABLE IF NOT EXISTS Track_list (
id SERIAL PRIMARY KEY NOT NULL,
Name_track VARCHAR(60) NOT NULL,
id_album INTEGER REFERENCES Albums_list(id),
track_duration TIME
);

CREATE TABLE IF NOT EXISTS Tracks_collecltion (
id_track INTEGER REFERENCES Track_list(id),
id_collection INTEGER REFERENCES Collection(id),
CONSTRAINT pk_tracks_collection PRIMARY KEY (id_track, id_collection)
);

CREATE TABLE Genres_performers (
id_genres INTEGER REFERENCES List_of_musical_genres(id),
id_performer INTEGER REFERENCES List_of_performers(id),
CONSTRAINT genres_singer_pkey PRIMARY KEY (id_genres, id_performer) -- связь между жанрами и исполнителями
);

CREATE TABLE Album_perfomers (
id_performer INTEGER REFERENCES List_of_performers(id),
id_album INTEGER REFERENCES Albums_list(id),
CONSTRAINT pk_singer_album PRIMARY KEY (id_performer, id_album) -- связь между исполнителями и альбомами
);