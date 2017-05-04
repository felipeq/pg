/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pt_lab4;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;

/**
 *
 * @author Filip
 */
public class PT_lab4 extends Application {

    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));

        Scene scene = new Scene(root);

        stage.setScene(scene);
        stage.show();
        dupe();
    }
    public void dupe() throws JAXBException
    {
        File file = new File("plik.xml");
        JAXBContext context = JAXBContext.newInstance(Catalog.class);
        Marshaller marshaller = context.createMarshaller();
        Catalog catalog = new Catalog();
        List<Book> catalogList = new ArrayList<>();
        Book book = new Book();
        book.setTitle("Harry Potter");
        book.setPages(100);
        catalogList.add(book);
        Book book1 = new Book();
        book1.setTitle("Władca Pierścieni");
        book1.setPages(200);
        catalogList.add(book1);
        catalog.setBooks(catalogList);
        marshaller.marshal(catalog, file);
        System.out.println("hehe");
    
    }
    /**
     * @param args the command line arguments
     * @throws javax.xml.bind.JAXBException
     */
    public static void main(String[] args) throws JAXBException {
        launch(args);
        

    }

}
