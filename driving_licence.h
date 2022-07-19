#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class DrivingLicence {
public:
    DrivingLicence()
        : doc_()
        , table_prt_(&DrivingLicence::TABLE)
    {
        doc_.table_prt_ = reinterpret_cast<IdentityDocument::Table*>(table_prt_);
        std::cout << "DrivingLicence::Ctor()"sv << std::endl;
    }

    DrivingLicence(const DrivingLicence& other)
        : doc_(other.doc_) 
        , table_prt_(&DrivingLicence::TABLE)
    {
        std::cout << "DrivingLicence::CCtor()"sv << std::endl;
    }

    ~DrivingLicence() {
        if (doc_.table_prt_
            == reinterpret_cast<IdentityDocument::Table*>(&DrivingLicence::TABLE)) {
            
            doc_.table_prt_ = &IdentityDocument::TABLE;
        }
        std::cout << "DrivingLicence::Dtor()"sv << std::endl;
    }

    int GetID() const {
        return doc_.GetID();
    }

    // ��� �������������� � �������� ����
    template <typename T>
    operator T() {
        auto ptr = reinterpret_cast<T*>(this);
        doc_.table_prt_ = reinterpret_cast<IdentityDocument::Table*>
            (&IdentityDocument::TABLE);
        return *ptr;
    }

    void PrintID() const {
        std::cout << "DrivingLicence::PrintID() : "sv << GetID() << std::endl;
    }

    void Delete() {
        this->~DrivingLicence();
    }

private:
    IdentityDocument doc_;
public:
    // ��������� ����������� ������� �������
    struct Table
    {
        void (DrivingLicence::* const PrintID)() const;
        void (DrivingLicence::* Delete)();
    };
    // ������� ��� ������� �����
    static Table TABLE;
    // ��������� �� �������?
    Table* table_prt_;
};


// ����������� �������
DrivingLicence::Table DrivingLicence::TABLE =
{ &DrivingLicence::PrintID, &DrivingLicence::Delete };