/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ptlab5;

import java.util.ArrayList;
import java.util.List;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.Query;

/**
 *
 * @author Filip
 */
public class DbController {

    public static Book BookSetter(Book book, String title, List<Author> authors) {
        book.setTitle(title);
        book.setAuthors(authors);
        return book;

    }

    public static Author AuthorConstructor(String name, String surname, Book book) {
        Author author = new Author();
        author.setBook(book);
        author.setName(name);
        author.setSurname(surname);
        return author;
    }

    public static void ExampleInserts() {

        for (int i = 0; i < 5; i++) {
            ArrayList<Author> authors = new ArrayList<>();
            Book book = new Book();
            authors.add(AuthorConstructor("Imię " + Integer.toString(i), "Nazwisko " + Integer.toString(i), book));
            authors.add(AuthorConstructor("Imię " + Integer.toString(i * 10), "Nazwisko" + Integer.toString(i * 10), book));
            persist(BookSetter(book, "Tytuł nr " + Integer.toString(i), authors));
        }

    }

    public static void persist(Object object) {

        EntityManagerFactory emf = Persistence.createEntityManagerFactory("ptlab5PU");
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();
        try {
            em.persist(object);
        } catch (Exception e) {
            em.getTransaction().rollback();
        } finally {
            em.getTransaction().commit();
            em.close();
        }
    }

    public static ObservableList GetBookList() {
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("ptlab5PU");
        EntityManager em = emf.createEntityManager();
        Query q = em.createQuery("select b from Book b");
        ObservableList<Book> observableList;
        observableList = FXCollections.observableList(q.getResultList());
        return observableList;

    }

    public static void update(Author author) {
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("ptlab5PU");
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();
        try {
            Author old = em.find(Author.class, author.getId());
            old.setName(author.getName());
            old.setSurname(author.getSurname());
            em.persist(old);
        } catch (Exception e) {
            em.getTransaction().rollback();
        } finally {
            em.getTransaction().commit();
            em.close();
        }
    }

    public static void update(Book book) {
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("ptlab5PU");
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();
        try {
            Book old = em.find(Book.class, book.getId());
            old.setTitle(book.getTitle());
            em.persist(old);
        } catch (Exception e) {
            em.getTransaction().rollback();
        } finally {
            em.getTransaction().commit();
            em.close();
        }
    }

}
