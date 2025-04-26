#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <memory>

using testing::AtLeast;
using testing::AtMost;
using testing::Return;
using testing::_;
using ::testing::InSequence;

// Some connection interface
struct IDataBaseConnection {
    virtual bool login(
        const std::string& user,
        const std::string& password) = 0;

    virtual bool logout() = 0;
};
/*
struct PostgresDataBaseConnection : public IDataBaseConnection
{
    virtual bool login(
        const std::string& user,
        const std::string& password) {}
    virtual bool logout() {}
};*/

struct DataBaseConnectionImpl : IDataBaseConnection {
    //real implementation with calls to db
};

// Some implementation of working with DB
struct DataBase {
    DataBase(
        IDataBaseConnection* connection,
        const std::string& user,
        const std::string& password
    ) : m_connection{connection}
        , m_user{user}
        , m_password{password} {
    }

    ~DataBase() {
        m_connection->logout();
    }

    bool connect() {
        if (!m_connection)
            return false;

        return m_connection->login(m_user, m_password);
        //return true;
    }
private:
    IDataBaseConnection *m_connection;
    std::string m_user;
    std::string m_password;
};


//gmock object implementation
struct MockDataBaseConnection : IDataBaseConnection {
    MOCK_METHOD(
        bool, 
        login, 
        (const std::string& user, const std::string& password), 
        (override)
    );

    MOCK_METHOD(
        bool,
        logout,
        (),
        (override)
    );
};


TEST(DBTest, LoginSuccess) {
    // Arrange
    const std::string usernameRef = "username";
    const std::string passwordRef = "password";
    MockDataBaseConnection mockConnection;
    
    DataBase database(
        &mockConnection, //pass mock to Database constructor
        usernameRef,
        passwordRef
    );

    //check that call will be performed
    EXPECT_CALL(mockConnection, login(_, _))
        .Times(AtLeast(1)).WillOnce(Return(true)); //set return value, because it's not a real implementation

    EXPECT_CALL(mockConnection, logout())
        .Times(AtLeast(1));

    // Act
    bool connectionResult = database.connect();

    // Assert
    ASSERT_TRUE(connectionResult);
}


TEST(DBTest, LoginUsernamePassword) {
    // Arrange
    const std::string usernameRef = "username";
    const std::string passwordRef = "password";
    MockDataBaseConnection mockConnection;
    
    DataBase database(
        &mockConnection,
        usernameRef,
        passwordRef
    );

    // Prepare mocks
    EXPECT_CALL(mockConnection, login(usernameRef, passwordRef))
        .Times(AtLeast(1))
        .WillOnce(Return(true));

    EXPECT_CALL(mockConnection, logout())
        .Times(AtLeast(1));

    // Act
    bool connectionResult = database.connect();

    // Assert
    ASSERT_TRUE(connectionResult);
}



TEST(DBTest, LoginFailure) {
    // Arrange
    const std::string usernameRef = "username";
    const std::string passwordRef = "password";
    MockDataBaseConnection mockConnection;
    
    DataBase database(
        &mockConnection,
        usernameRef,
        passwordRef
    );


    EXPECT_CALL(mockConnection, logout())
        .Times(AtLeast(1));
        
    // Prepare mocks
    EXPECT_CALL(mockConnection, login(usernameRef, passwordRef)) //will check args
        .Times(AtLeast(1))
        .WillOnce(Return(false));


    // Act
    bool connectionResult = database.connect();

    // Assert
    ASSERT_FALSE(connectionResult);
}

TEST(DBTest, CheckSequence) {
    // Arrange
    const std::string usernameRef = "username";
    const std::string passwordRef = "password";
    MockDataBaseConnection mockConnection;

    DataBase database(
        &mockConnection, //pass mock to Database constructor
        usernameRef,
        passwordRef
    );

    {
        InSequence s;
        EXPECT_CALL(mockConnection, logout())
            .Times(AtLeast(1));

        //check that call will be performed
        EXPECT_CALL(mockConnection, login(_, _)) //placeholders if we are not interested in params
            .Times(AtLeast(1)) //expect at least 1 call
            .WillOnce(Return(true)); //set return value, because it's not a real implementation
    }
    // Act
    bool connectionResult = database.connect();
    // Assert
    ASSERT_TRUE(connectionResult);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
