CREATE TABLE book (
    id CHAR(20) PRIMARY KEY,
    title VARCHAR NOT NULL
);

CREATE TABLE reader (
    id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL
);

CREATE TABLE borrow (
    id SERIAL PRIMARY KEY,
    book CHAR(20) NOT NULL,
    reader INT NOT NULL,
    borrow_date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    return_date TIMESTAMP,
    FOREIGN KEY (book) REFERENCES book(id) ON DELETE CASCADE,
    FOREIGN KEY (reader) REFERENCES reader(id) ON DELETE CASCADE
);

INSERT INTO book (title, id) VALUES
    ('Pride and Prejudice', '978-0141439518'),
    ('1984', '978-0451524935'),
    ('To Kill a Mockingbird', '978-0061120084');