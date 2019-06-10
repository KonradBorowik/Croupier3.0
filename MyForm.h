#include <string>
#include "PlayersInteraction.h"
#include "Table.h"

#pragma once

namespace Croupier30 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Collections::Generic;

	extern Table table;

	int deal = 0;
	int number_of_players = 0;



	std::vector<Player>::iterator dealer;
	std::vector<Player>::iterator player_to_wait_for;
	std::vector<Player>::iterator current_player;
	auto all_players_acted = false;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ AddPlayerButton;
	private: System::Windows::Forms::TextBox^ AddPlayerBox;
	protected:

	private: System::Windows::Forms::Button^ StartButton;
	private: System::Windows::Forms::GroupBox^ PlayerBox;
	private: System::Windows::Forms::Label^ CurrentBidLabel;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ WinnerButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ CashLabel;
	private: System::Windows::Forms::GroupBox^ MoneyBox;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ BigBlindBox;
	private: System::Windows::Forms::TextBox^ SmallBlindBox;
	private: System::Windows::Forms::TextBox^ BuyInBox;
	private: System::Windows::Forms::Button^ NewGameButton;
	private: System::Windows::Forms::GroupBox^ TableBox;
	private: System::Windows::Forms::Label^ RoundLabel;
	private: System::Windows::Forms::Label^ HighestBidLabel;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ StackLabel;
	private: System::Windows::Forms::GroupBox^ InteractionBox;
	private: System::Windows::Forms::Button^ FoldButton;
	private: System::Windows::Forms::Button^ AllInButton;
	private: System::Windows::Forms::Button^ RaiseButton;
	private: System::Windows::Forms::Button^ CallButton;
	private: System::Windows::Forms::Button^ BidButton;
	private: System::Windows::Forms::Button^ CheckButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->AddPlayerButton = (gcnew System::Windows::Forms::Button());
			this->AddPlayerBox = (gcnew System::Windows::Forms::TextBox());
			this->StartButton = (gcnew System::Windows::Forms::Button());
			this->PlayerBox = (gcnew System::Windows::Forms::GroupBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->CashLabel = (gcnew System::Windows::Forms::Label());
			this->CurrentBidLabel = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->WinnerButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->MoneyBox = (gcnew System::Windows::Forms::GroupBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->NewGameButton = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->BigBlindBox = (gcnew System::Windows::Forms::TextBox());
			this->SmallBlindBox = (gcnew System::Windows::Forms::TextBox());
			this->BuyInBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->TableBox = (gcnew System::Windows::Forms::GroupBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->HighestBidLabel = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->StackLabel = (gcnew System::Windows::Forms::Label());
			this->RoundLabel = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->InteractionBox = (gcnew System::Windows::Forms::GroupBox());
			this->FoldButton = (gcnew System::Windows::Forms::Button());
			this->AllInButton = (gcnew System::Windows::Forms::Button());
			this->RaiseButton = (gcnew System::Windows::Forms::Button());
			this->CallButton = (gcnew System::Windows::Forms::Button());
			this->BidButton = (gcnew System::Windows::Forms::Button());
			this->CheckButton = (gcnew System::Windows::Forms::Button());
			this->PlayerBox->SuspendLayout();
			this->MoneyBox->SuspendLayout();
			this->TableBox->SuspendLayout();
			this->InteractionBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// AddPlayerButton
			// 
			this->AddPlayerButton->Location = System::Drawing::Point(12, 12);
			this->AddPlayerButton->Name = L"AddPlayerButton";
			this->AddPlayerButton->Size = System::Drawing::Size(75, 23);
			this->AddPlayerButton->TabIndex = 0;
			this->AddPlayerButton->Text = L"Add Player";
			this->AddPlayerButton->UseVisualStyleBackColor = true;
			this->AddPlayerButton->Visible = false;
			this->AddPlayerButton->Click += gcnew System::EventHandler(this, &MyForm::AddPlayerButton_Click);
			// 
			// AddPlayerBox
			// 
			this->AddPlayerBox->Location = System::Drawing::Point(162, 14);
			this->AddPlayerBox->Name = L"AddPlayerBox";
			this->AddPlayerBox->Size = System::Drawing::Size(100, 20);
			this->AddPlayerBox->TabIndex = 1;
			this->AddPlayerBox->Visible = false;
			this->AddPlayerBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::AddPlayerBox_KeyPress);
			// 
			// StartButton
			// 
			this->StartButton->Location = System::Drawing::Point(268, 14);
			this->StartButton->Name = L"StartButton";
			this->StartButton->Size = System::Drawing::Size(75, 23);
			this->StartButton->TabIndex = 2;
			this->StartButton->Text = L"Start";
			this->StartButton->UseVisualStyleBackColor = true;
			this->StartButton->Visible = false;
			this->StartButton->Click += gcnew System::EventHandler(this, &MyForm::StartButton_Click);
			// 
			// PlayerBox
			// 
			this->PlayerBox->Controls->Add(this->CashLabel);
			this->PlayerBox->Controls->Add(this->CurrentBidLabel);
			this->PlayerBox->Controls->Add(this->label2);
			this->PlayerBox->Controls->Add(this->WinnerButton);
			this->PlayerBox->Controls->Add(this->label1);
			this->PlayerBox->Location = System::Drawing::Point(12, 41);
			this->PlayerBox->Name = L"PlayerBox";
			this->PlayerBox->Size = System::Drawing::Size(200, 100);
			this->PlayerBox->TabIndex = 3;
			this->PlayerBox->TabStop = false;
			this->PlayerBox->Text = L"groupBox1";
			this->PlayerBox->Visible = false;
			// 
			// label11
			// 
			this->label11->Location = System::Drawing::Point(580, 41);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(100, 23);
			this->label11->TabIndex = 0;
			// 
			// CashLabel
			// 
			this->CashLabel->AutoSize = true;
			this->CashLabel->Location = System::Drawing::Point(93, 16);
			this->CashLabel->Name = L"CashLabel";
			this->CashLabel->Size = System::Drawing::Size(73, 13);
			this->CashLabel->TabIndex = 4;
			this->CashLabel->Text = L"Cash zmienna";
			// 
			// CurrentBidLabel
			// 
			this->CurrentBidLabel->AutoSize = true;
			this->CurrentBidLabel->Location = System::Drawing::Point(93, 39);
			this->CurrentBidLabel->Name = L"CurrentBidLabel";
			this->CurrentBidLabel->Size = System::Drawing::Size(101, 13);
			this->CurrentBidLabel->TabIndex = 3;
			this->CurrentBidLabel->Text = L"Current Bid zmienna";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 39);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Current Bid";
			// 
			// WinnerButton
			// 
			this->WinnerButton->Location = System::Drawing::Point(119, 71);
			this->WinnerButton->Name = L"WinnerButton";
			this->WinnerButton->Size = System::Drawing::Size(75, 23);
			this->WinnerButton->TabIndex = 1;
			this->WinnerButton->Text = L"Winner";
			this->WinnerButton->UseVisualStyleBackColor = true;
			this->WinnerButton->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Cash";
			// 
			// MoneyBox
			// 
			this->MoneyBox->Controls->Add(this->label10);
			this->MoneyBox->Controls->Add(this->NewGameButton);
			this->MoneyBox->Controls->Add(this->label5);
			this->MoneyBox->Controls->Add(this->label4);
			this->MoneyBox->Controls->Add(this->BigBlindBox);
			this->MoneyBox->Controls->Add(this->SmallBlindBox);
			this->MoneyBox->Controls->Add(this->BuyInBox);
			this->MoneyBox->Location = System::Drawing::Point(304, 41);
			this->MoneyBox->Name = L"MoneyBox";
			this->MoneyBox->Size = System::Drawing::Size(200, 130);
			this->MoneyBox->TabIndex = 4;
			this->MoneyBox->TabStop = false;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(6, 74);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(48, 13);
			this->label10->TabIndex = 7;
			this->label10->Text = L"Big Blind";
			// 
			// NewGameButton
			// 
			this->NewGameButton->Location = System::Drawing::Point(61, 101);
			this->NewGameButton->Name = L"NewGameButton";
			this->NewGameButton->Size = System::Drawing::Size(75, 23);
			this->NewGameButton->TabIndex = 6;
			this->NewGameButton->Text = L"New Game";
			this->NewGameButton->UseVisualStyleBackColor = true;
			this->NewGameButton->Click += gcnew System::EventHandler(this, &MyForm::NewGameButton_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 48);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(58, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Small Blind";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(37, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Buy In";
			// 
			// BigBlindBox
			// 
			this->BigBlindBox->Location = System::Drawing::Point(94, 71);
			this->BigBlindBox->Name = L"BigBlindBox";
			this->BigBlindBox->Size = System::Drawing::Size(100, 20);
			this->BigBlindBox->TabIndex = 2;
			this->BigBlindBox->Text = L"10";
			// 
			// SmallBlindBox
			// 
			this->SmallBlindBox->Location = System::Drawing::Point(94, 45);
			this->SmallBlindBox->Name = L"SmallBlindBox";
			this->SmallBlindBox->Size = System::Drawing::Size(100, 20);
			this->SmallBlindBox->TabIndex = 1;
			this->SmallBlindBox->Text = L"5";
			// 
			// BuyInBox
			// 
			this->BuyInBox->Location = System::Drawing::Point(94, 19);
			this->BuyInBox->Name = L"BuyInBox";
			this->BuyInBox->Size = System::Drawing::Size(100, 20);
			this->BuyInBox->TabIndex = 0;
			this->BuyInBox->Text = L"100";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(93, 17);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Enter Name";
			this->label3->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(144, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 6;
			this->label6->Text = L"Stack";
			// 
			// TableBox
			// 
			this->TableBox->Controls->Add(this->label9);
			this->TableBox->Controls->Add(this->HighestBidLabel);
			this->TableBox->Controls->Add(this->label7);
			this->TableBox->Controls->Add(this->label6);
			this->TableBox->Controls->Add(this->StackLabel);
			this->TableBox->Controls->Add(this->RoundLabel);
			this->TableBox->Location = System::Drawing::Point(43, 205);
			this->TableBox->Name = L"TableBox";
			this->TableBox->Size = System::Drawing::Size(561, 50);
			this->TableBox->TabIndex = 5;
			this->TableBox->TabStop = false;
			this->TableBox->Text = L"Table";
			this->TableBox->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(467, 16);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(29, 13);
			this->label9->TabIndex = 8;
			this->label9->Text = L"Deal";
			// 
			// HighestBidLabel
			// 
			this->HighestBidLabel->AutoSize = true;
			this->HighestBidLabel->Location = System::Drawing::Point(384, 16);
			this->HighestBidLabel->Name = L"HighestBidLabel";
			this->HighestBidLabel->Size = System::Drawing::Size(35, 13);
			this->HighestBidLabel->TabIndex = 9;
			this->HighestBidLabel->Text = L"label3";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(319, 16);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(61, 13);
			this->label7->TabIndex = 8;
			this->label7->Text = L"Highest Bid";
			// 
			// StackLabel
			// 
			this->StackLabel->AutoSize = true;
			this->StackLabel->Location = System::Drawing::Point(196, 16);
			this->StackLabel->Name = L"StackLabel";
			this->StackLabel->Size = System::Drawing::Size(35, 13);
			this->StackLabel->TabIndex = 7;
			this->StackLabel->Text = L"label7";
			// 
			// RoundLabel
			// 
			this->RoundLabel->AutoSize = true;
			this->RoundLabel->Location = System::Drawing::Point(9, 16);
			this->RoundLabel->Name = L"RoundLabel";
			this->RoundLabel->Size = System::Drawing::Size(35, 13);
			this->RoundLabel->TabIndex = 6;
			this->RoundLabel->Text = L"label6";
			// 
			// label8
			// 
			this->label8->Location = System::Drawing::Point(0, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(100, 23);
			this->label8->TabIndex = 0;
			// 
			// InteractionBox
			// 
			this->InteractionBox->Controls->Add(this->FoldButton);
			this->InteractionBox->Controls->Add(this->AllInButton);
			this->InteractionBox->Controls->Add(this->RaiseButton);
			this->InteractionBox->Controls->Add(this->CallButton);
			this->InteractionBox->Controls->Add(this->BidButton);
			this->InteractionBox->Controls->Add(this->CheckButton);
			this->InteractionBox->Location = System::Drawing::Point(12, 350);
			this->InteractionBox->Name = L"InteractionBox";
			this->InteractionBox->Size = System::Drawing::Size(200, 138);
			this->InteractionBox->TabIndex = 6;
			this->InteractionBox->TabStop = false;
			this->InteractionBox->Text = L"Interaction";
			this->InteractionBox->Visible = false;
			// 
			// FoldButton
			// 
			this->FoldButton->Location = System::Drawing::Point(58, 106);
			this->FoldButton->Name = L"FoldButton";
			this->FoldButton->Size = System::Drawing::Size(75, 23);
			this->FoldButton->TabIndex = 5;
			this->FoldButton->Text = L"Fold";
			this->FoldButton->UseVisualStyleBackColor = true;
			this->FoldButton->Click += gcnew System::EventHandler(this, &MyForm::FoldButton_Click);
			// 
			// AllInButton
			// 
			this->AllInButton->Location = System::Drawing::Point(58, 77);
			this->AllInButton->Name = L"AllInButton";
			this->AllInButton->Size = System::Drawing::Size(75, 23);
			this->AllInButton->TabIndex = 4;
			this->AllInButton->Text = L"All In";
			this->AllInButton->UseVisualStyleBackColor = true;
			this->AllInButton->Click += gcnew System::EventHandler(this, &MyForm::AllInButton_Click);
			// 
			// RaiseButton
			// 
			this->RaiseButton->Location = System::Drawing::Point(58, 48);
			this->RaiseButton->Name = L"RaiseButton";
			this->RaiseButton->Size = System::Drawing::Size(75, 23);
			this->RaiseButton->TabIndex = 3;
			this->RaiseButton->Text = L"Rasie";
			this->RaiseButton->UseVisualStyleBackColor = true;
			this->RaiseButton->Visible = false;
			this->RaiseButton->Click += gcnew System::EventHandler(this, &MyForm::RaiseButton_Click);
			// 
			// CallButton
			// 
			this->CallButton->Location = System::Drawing::Point(58, 19);
			this->CallButton->Name = L"CallButton";
			this->CallButton->Size = System::Drawing::Size(75, 23);
			this->CallButton->TabIndex = 2;
			this->CallButton->Text = L"Call";
			this->CallButton->UseVisualStyleBackColor = true;
			this->CallButton->Visible = false;
			this->CallButton->Click += gcnew System::EventHandler(this, &MyForm::CallButton_Click);
			// 
			// BidButton
			// 
			this->BidButton->Location = System::Drawing::Point(58, 48);
			this->BidButton->Name = L"BidButton";
			this->BidButton->Size = System::Drawing::Size(75, 23);
			this->BidButton->TabIndex = 1;
			this->BidButton->Text = L"Bid";
			this->BidButton->UseVisualStyleBackColor = true;
			this->BidButton->Visible = false;
			this->BidButton->Click += gcnew System::EventHandler(this, &MyForm::BidButton_Click);
			// 
			// CheckButton
			// 
			this->CheckButton->Location = System::Drawing::Point(58, 19);
			this->CheckButton->Name = L"CheckButton";
			this->CheckButton->Size = System::Drawing::Size(75, 23);
			this->CheckButton->TabIndex = 0;
			this->CheckButton->Text = L"Check";
			this->CheckButton->UseVisualStyleBackColor = true;
			this->CheckButton->Visible = false;
			this->CheckButton->Click += gcnew System::EventHandler(this, &MyForm::CheckButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(954, 544);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->InteractionBox);
			this->Controls->Add(this->TableBox);
			this->Controls->Add(this->MoneyBox);
			this->Controls->Add(this->PlayerBox);
			this->Controls->Add(this->StartButton);
			this->Controls->Add(this->AddPlayerBox);
			this->Controls->Add(this->AddPlayerButton);
			this->Name = L"MyForm";
			this->Text = L"Croupier3.0";
			this->PlayerBox->ResumeLayout(false);
			this->PlayerBox->PerformLayout();
			this->MoneyBox->ResumeLayout(false);
			this->MoneyBox->PerformLayout();
			this->TableBox->ResumeLayout(false);
			this->TableBox->PerformLayout();
			this->InteractionBox->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		void UpdatePlayerStatus();

		void MoveIntercationBox();

		void FinishMove();

		System::Void WinnerButton_Click(System::Object^ sender, System::EventArgs^ e);

		ref class PlayerGroupBox : public System::Windows::Forms::GroupBox {
		public:
			System::Windows::Forms::Button^ WinnerButton;
			System::Windows::Forms::Label^ CashLabel;
			System::Windows::Forms::Label^ CurrentBidLabel;
			System::Windows::Forms::Label^ BlindLabel;
			int player_number;
			System::Windows::Forms::Label^ CashPrompt;
			System::Windows::Forms::Label^ CurrentBidPrompt;
			void Update();
			System::Windows::Forms::Label^ StatusInfoLabel;
			
		};

		List<PlayerGroupBox^> PlayerGroupBoxes;

private: System::Void AddPlayerButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void NewGameButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void StartButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void AddPlayerBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
private: System::Void CheckButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void CallButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void RaiseButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void BidButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void AllInButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void FoldButton_Click(System::Object^ sender, System::EventArgs^ e);
};
}
