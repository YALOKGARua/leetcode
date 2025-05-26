WITH RECURSIVE hierarchy AS (
    SELECT 
        employee_id,
        employee_name,
        manager_id,
        salary,
        1 as level
    FROM Employees
    WHERE manager_id IS NULL
    
    UNION ALL
    
    SELECT 
        e.employee_id,
        e.employee_name,
        e.manager_id,
        e.salary,
        h.level + 1
    FROM Employees e
    JOIN hierarchy h ON e.manager_id = h.employee_id
),

subordinates AS (
    SELECT 
        h1.employee_id as manager_id,
        h2.employee_id as subordinate_id
    FROM hierarchy h1
    JOIN hierarchy h2 ON h2.manager_id = h1.employee_id
    
    UNION ALL
    
    SELECT 
        s.manager_id,
        h.employee_id
    FROM subordinates s
    JOIN hierarchy h ON h.manager_id = s.subordinate_id
),

team_sizes AS (
    SELECT 
        manager_id,
        COUNT(DISTINCT subordinate_id) as team_size
    FROM subordinates
    GROUP BY manager_id
),

budgets AS (
    SELECT 
        h.employee_id,
        h.salary + COALESCE(SUM(e.salary), 0) as budget
    FROM hierarchy h
    LEFT JOIN subordinates s ON h.employee_id = s.manager_id
    LEFT JOIN hierarchy e ON e.employee_id = s.subordinate_id
    GROUP BY h.employee_id, h.salary
)

SELECT 
    h.employee_id,
    h.employee_name,
    h.level,
    COALESCE(ts.team_size, 0) as team_size,
    b.budget
FROM hierarchy h
LEFT JOIN team_sizes ts ON h.employee_id = ts.manager_id
LEFT JOIN budgets b ON h.employee_id = b.employee_id
ORDER BY h.level, b.budget DESC, h.employee_name; 