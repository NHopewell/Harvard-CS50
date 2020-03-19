SELECT DISTINCT(m.title)
FROM movies m
JOIN ratings r
	ON m.id = r.movie_id
JOIN stars s
	ON m.id = s.movie_id
JOIN people p
	ON s.person_id = p.id
WHERE r.movie_id IN (
			SELECT ratings.movie_id 
			FROM ratings 
			JOIN stars 
				ON ratings.movie_id = stars.movie_id
			JOIN people 
				ON stars.person_id = people.id
				AND people.name = 'Chadwick Boseman'
			ORDER BY 
				ratings.rating DESC 
			LIMIT 5
		);