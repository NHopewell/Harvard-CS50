SELECT movies.title 
FROM movies
WHERE movies.id IN
( 
	SELECT m.id FROM people p
	JOIN stars s
		ON p.id = s.person_id
	JOIN movies m
		ON s.movie_id = m.id
	WHERE p.name IN ("Johnny Depp", "Helena Bonham Carter")
	GROUP BY 
		m.id HAVING COUNT(*)=2 
);