#pragma once

#include <iostream>
#include <string>

using namespace std::string_view_literals;

class IdentityDocument {
public:
    IdentityDocument()
        : unique_id_(++unique_id_count_)
        , table_prt_(&IdentityDocument::TABLE)
    {
        std::cout << "IdentityDocument::Ctor() : "sv << unique_id_ << std::endl;
    }

    ~IdentityDocument() {
        --unique_id_count_;
        std::cout << "IdentityDocument::Dtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument(const IdentityDocument& other)
        : unique_id_(++unique_id_count_)
        , table_prt_(other.table_prt_)
    {
        std::cout << "IdentityDocument::CCtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument& operator=(const IdentityDocument&) = delete;

    void PrintID() const {
        // 
        if (&IdentityDocument::PrintID == table_prt_->PrintID) {
            std::cout << "IdentityDocument::PrintID() : "sv << unique_id_ << std::endl;
        }
        // 
        else {
            (this->*(table_prt_->PrintID))();
        }
    }

    static void PrintUniqueIDCount() {
        std::cout << "unique_id_count_ : "sv << unique_id_count_ << std::endl;
    }

    void Delete() {
        if (&IdentityDocument::Delete == table_prt_->Delete) {
            this->~IdentityDocument();
        }
        else {
            (this->*(table_prt_->Delete))();
        }

    }

    int GetID() const {
        return unique_id_;
    }

private:
    static int unique_id_count_;
    int unique_id_;

public:
    // Структура виртуальной таблицы методов
    struct Table
    {
        void (IdentityDocument::* const PrintID)() const;
        void (IdentityDocument::* Delete)();
    };
    // Таблица для данного класс
    static Table TABLE;
    // Указатель на таблицу?
    Table* table_prt_;
};

int IdentityDocument::unique_id_count_ = 0;
// Определение таблицы
IdentityDocument::Table IdentityDocument::TABLE =
{ &IdentityDocument::PrintID, &IdentityDocument::Delete };