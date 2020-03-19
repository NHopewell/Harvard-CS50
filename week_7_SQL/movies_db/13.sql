SELECT p.name FROM people p
JOIN stars s 
	ON p.id = s.person_id
JOIN movies m
	ON s.movie_id = m.id
WHERE m.id IN (
	SELECT movies.id FROM movies
	JOIN stars 
		ON movies.id = stars.movie_id
	JOIN people	
		ON stars.person_id = people.id
		AND people.name = 'Kevin Bacon'
		AND people.birth = 1958
) AND
p.name != 'Kevin Bacon';