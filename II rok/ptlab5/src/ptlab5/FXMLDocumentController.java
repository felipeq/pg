/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ptlab5;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.property.ListProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableColumn.CellEditEvent;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.util.converter.LongStringConverter;

/**
 *
 * @author Filip
 */
public class FXMLDocumentController implements Initializable {

    @FXML
    private Label label;
    @FXML
    private TableView tableView;
    @FXML
    private TableColumn titleColumn;
    @FXML
    private TableColumn bookIDColumn;
    @FXML
    private TableView authorsTableView;
    @FXML
    private TableColumn authorIDColumn;
    @FXML
    private TableColumn nameColumn;
    @FXML
    private TableColumn surnameColumn;
    private ListProperty<Author> authors = new SimpleListProperty<>();

    class BookChangeListener implements ChangeListener<Book> {

        @Override
        public void changed(ObservableValue<? extends Book> value, Book oldV, Book newV) {
            if (newV != null) {
                ObservableList<Author> observableList;
                observableList = FXCollections.observableList(newV.getAuthors());
                authors.set(observableList);
            } else {
                authors.setValue(null);
            }
        }
    }

    @FXML
    private void handleButtonAction(ActionEvent event) {
        System.out.println("You clicked me!");
        label.setText("Hello World!");
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {

        tableView.setEditable(true);
        authorsTableView.setEditable(true);

        bookIDColumn.setCellValueFactory(new PropertyValueFactory<Event, String>("id"));
        bookIDColumn.setCellFactory(TextFieldTableCell.forTableColumn(new LongStringConverter()));
        titleColumn.setCellValueFactory(new PropertyValueFactory<Event, String>("title"));

        authorIDColumn.setCellValueFactory(new PropertyValueFactory<Event, String>("id"));
        nameColumn.setCellValueFactory(new PropertyValueFactory<Event, String>("name"));
        surnameColumn.setCellValueFactory(new PropertyValueFactory<Event, String>("surname"));

        titleColumn.setCellFactory(TextFieldTableCell.forTableColumn());
        nameColumn.setCellFactory(TextFieldTableCell.forTableColumn());
        surnameColumn.setCellFactory(TextFieldTableCell.forTableColumn());

        titleColumn.setOnEditCommit(new EventHandler<CellEditEvent<Book, String>>() {
            @Override
            public void handle(CellEditEvent<Book, String> t) {
                Book book = t.getRowValue();
                String newTitle = t.getNewValue();
                book.setTitle(newTitle);
                DbController.update(book);
            }
        });
        nameColumn.setOnEditCommit(new EventHandler<CellEditEvent<Author, String>>() {
            @Override
            public void handle(CellEditEvent<Author, String> t) {
                Author author = t.getRowValue();
                String newName = t.getNewValue();
                author.setName(newName);
                DbController.update(author);
            }
        });
        surnameColumn.setOnEditCommit(new EventHandler<CellEditEvent<Author, String>>() {
            @Override
            public void handle(CellEditEvent<Author, String> t) {
                Author author = t.getRowValue();
                String newSurname = t.getNewValue();
                author.setSurname(newSurname);
                DbController.update(author);
            }
        });
        authorsTableView.itemsProperty().bind(authors);
        tableView.getSelectionModel().selectedItemProperty().
                addListener(new BookChangeListener());

        tableView.setItems(DbController.GetBookList());

    }

}
