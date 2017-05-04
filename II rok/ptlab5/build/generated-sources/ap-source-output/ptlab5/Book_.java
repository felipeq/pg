package ptlab5;

import javax.annotation.Generated;
import javax.persistence.metamodel.ListAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import ptlab5.Author;

@Generated(value="EclipseLink-2.5.1.v20130918-rNA", date="2014-04-10T14:29:17")
@StaticMetamodel(Book.class)
public class Book_ { 

    public static volatile SingularAttribute<Book, Long> id;
    public static volatile ListAttribute<Book, Author> authors;
    public static volatile SingularAttribute<Book, String> title;

}