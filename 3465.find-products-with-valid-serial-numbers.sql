SELECT product_id, product_name, description
FROM products
WHERE description REGEXP '(^|[^A-Za-z0-9])SN[0-9]{4}-[0-9]{4}([^0-9]|$)' COLLATE utf8mb4_bin
ORDER BY product_id; 