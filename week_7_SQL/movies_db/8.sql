SELECT name
FROM people p 
JOIN stars s
	ON p.id = s.person_id
JOIN movies m
	ON s.movie_id = m.id
	AND m.title = 'Toy Story';
	
	