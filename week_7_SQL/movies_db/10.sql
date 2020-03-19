SELECT name
FROM people p
JOIN stars s
	ON p.id = s.person_id
JOIN ratings r
	ON s.movie_id = r.movie_id
	AND r.rating >= 9.0;