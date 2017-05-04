package ptlab5;

import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import ptlab5.Book;

@Generated(value="EclipseLink-2.5.1.v20130918-rNA", date="2014-04-10T16:08:49")
@StaticMetamodel(Author.class)
public class Author_ { 

    public static volatile SingularAttribute<Author, Long> id;
    public static volatile SingularAttribute<Author, String> name;
    public static volatile SingularAttribute<Author, Book> book;
    public static volatile SingularAttribute<Author, String> surname;

}