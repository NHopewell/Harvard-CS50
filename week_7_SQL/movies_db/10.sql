SELECT p.name
FROM people p
JOIN directors d
	ON p.id = d.person_id
JOIN ratings r
	ON d.movie_id = r.movie_id
	AND r.rating >= 9.0;