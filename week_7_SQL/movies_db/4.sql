SELECT COUNT(*)
FROM movies m
JOIN ratings r
	ON m.id = r.movie_id
WHERE r.rating = 10.0