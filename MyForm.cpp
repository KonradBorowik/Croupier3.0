#include "MyForm.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Croupier30::MyForm form;
	Application::Run(% form);
}

namespace Croupier30 {
	Table table;

	System::Void MyForm::AddPlayerButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->AddPlayerBox->Visible = true;
		this->label3->Visible = true;
		AddPlayerBox->Focus();
	}
	
	System::Void MyForm::NewGameButton_Click(System::Object^ sender, System::EventArgs^ e) {
		//if (BuyInBox->Text == "") {
		//	MessageBox::Show("Add Buy-in!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Information);
		//}
		//if (SmallBlindBox->Text == "") {
		//	MessageBox::Show("Add Small blind!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Information);
		//}
		//if (BigBlindBox->Text == "") {
		//	MessageBox::Show("Add Big blind!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Information);
		//}

		try {
			table.buy_in = Convert::ToInt32(BuyInBox->Text);
		} catch (...) {
			BuyInBox->Focus();
			BuyInBox->Text = "";
			return;
		}

		try {
			table.small_blind = Convert::ToInt32(SmallBlindBox->Text);
		} catch (...) {
			SmallBlindBox->Focus();
			SmallBlindBox->Text = "";
			return;
		}

		try {
			table.big_blind = Convert::ToInt32(BigBlindBox->Text);
		} catch (...) {
			BigBlindBox->Focus();
			BigBlindBox->Text = "";
			return;
		}
		
		this->MoneyBox->Visible = false;
		this->AddPlayerButton->Visible = true;
	}

	std::vector<Player>::iterator next_active_player(std::vector<Player>::iterator current_player) {
		current_player++;
		if (current_player == table.players.end()) {
			current_player = table.players.begin();
		}
		if (!current_player->folded && current_player->cash > 0) {
			return current_player;
		}
		else {
			return next_active_player(current_player);
		}
	}

	void MyForm::MoveIntercationBox() {
		if (table.highest_bid == current_player->current_bid) {
			CheckButton->Visible = true;
			BidButton->Visible = true;
			CallButton->Visible = false;
			RaiseButton->Visible = false;
		}
		else {
			CheckButton->Visible = false;
			BidButton->Visible = false;
			CallButton->Visible = true;
			RaiseButton->Visible = true;
		}
		auto n = std::distance(table.players.begin(), current_player);
		this->InteractionBox->Location = System::Drawing::Point(12 + 210 * n, InteractionBox->Location.Y);

	}

	Void MyForm::UpdatePlayerStatus() {
		for each (PlayerGroupBox ^ pgb in PlayerGroupBoxes) {
			pgb->Update();
		}
	}

	void MyForm::FinishMove() {
		
		StackLabel->Text = Convert::ToString(table.stack);
		HighestBidLabel->Text = Convert::ToString(table.highest_bid);

		if (player_to_wait_for == current_player) {
			all_players_acted = true;
		}

		if (table.number_of_players_with_cash()) {
			current_player = next_active_player(current_player);
		}

		if ((!table.all_players_called() || !all_players_acted) && table.number_of_players_with_cash() >= 1 && table.number_of_players_not_folded() >= 2) {
			MoveIntercationBox();
		}
		else {
			if (table.round < 3 && table.number_of_players_with_cash() >= 2 && table.number_of_players_not_folded() >= 2) {
				table.round += 1;

				table.highest_bid = 0;
				for (auto& player : table.players) {
					player.current_bid = 0;
				}

				auto round_names = std::vector<std::string>{ "Preflop", "Flop", "Turn", "River" };
				RoundLabel->Text = msclr::interop::marshal_as<System::String^>(round_names[table.round]);

				player_to_wait_for = dealer;
				current_player = next_active_player(dealer);

				//interaction.round_counter(newtable.round);
				all_players_acted = false;
				MoveIntercationBox();
			}
			else {
				InteractionBox->Visible = false;
				for each (PlayerGroupBox ^ pgb in PlayerGroupBoxes) {
					pgb->WinnerButton->Visible = true;
				}


			}
		}

		UpdatePlayerStatus();

	}

	System::Void MyForm::WinnerButton_Click(System::Object^ sender, System::EventArgs^ e) {

		auto button = (Button^)sender;
		auto groupbox = (PlayerGroupBox^)button->Parent;
		table.players[groupbox->player_number].cash += table.stack;

		table.stack = 0;
		for (auto& player : table.players) {
			player.folded = false;
			player.current_bid = 0;
		}

		StackLabel->Text = Convert::ToString(table.stack);
		HighestBidLabel->Text = Convert::ToString(table.highest_bid);
		
		for each (PlayerGroupBox ^ pgb in PlayerGroupBoxes) {
			pgb->Update();
			pgb->WinnerButton->Visible = false;
		}		

		StartButton->Visible = true;
	}

	System::Void MyForm::StartButton_Click(System::Object^ sender, System::EventArgs^ e) {
		TableBox->Visible = true;
		StartButton->Visible = false;
		AddPlayerButton->Visible = false;
		InteractionBox->Visible = true;
		deal++;
		dealer = table.players.begin() + (deal - 1) % table.players.size();
		current_player = next_active_player(dealer);

		RoundLabel->Text = "Preflop";

		current_player->smallblind();
		current_player = next_active_player(current_player);
		current_player->bigblind();
		player_to_wait_for = current_player;
		current_player = next_active_player(current_player);

		UpdatePlayerStatus();

		StackLabel->Text = Convert::ToString(table.stack);
		HighestBidLabel->Text = Convert::ToString(table.highest_bid);

		MoveIntercationBox();
	}

	System::Void MyForm::AddPlayerBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar != '\r') {
			return;
		}



		this->label3->Visible = false;
		AddPlayerBox->Visible = false;

		System::Windows::Forms::TextBox^ textBox = (System::Windows::Forms::TextBox^)sender;

		auto groupBox = gcnew PlayerGroupBox();
		groupBox->Visible = true;
		groupBox->Location = System::Drawing::Point(12 + number_of_players++ * 210, 41);
		groupBox->Name = L"groupBox1";
		groupBox->Size = System::Drawing::Size(200, 90);
		groupBox->TabIndex = 1;
		groupBox->TabStop = false;
		groupBox->Text = textBox->Text;

		groupBox->CashPrompt = (gcnew System::Windows::Forms::Label());
		groupBox->CashPrompt->AutoSize = true;
		groupBox->CashPrompt->Location = System::Drawing::Point(16, 16);
		groupBox->CashPrompt->Name = L"label1";
		groupBox->CashPrompt->Size = System::Drawing::Size(30, 13);
		groupBox->CashPrompt->TabIndex = 2;
		groupBox->CashPrompt->Text = L"cash";
		groupBox->Controls->Add(groupBox->CashPrompt);

		groupBox->CurrentBidPrompt = (gcnew System::Windows::Forms::Label());
		groupBox->CurrentBidPrompt->AutoSize = true;
		groupBox->CurrentBidPrompt->Location = System::Drawing::Point(10, 36);
		groupBox->CurrentBidPrompt->Name = L"label2";
		groupBox->CurrentBidPrompt->Size = System::Drawing::Size(50, 13);
		groupBox->CurrentBidPrompt->TabIndex = 3;
		groupBox->CurrentBidPrompt->Text = L"current bid";
		groupBox->Controls->Add(groupBox->CurrentBidPrompt);

		groupBox->CashLabel = (gcnew System::Windows::Forms::Label());
		groupBox->CashLabel->AutoSize = true;
		groupBox->CashLabel->Location = System::Drawing::Point(66, 16);
		groupBox->CashLabel->Name = L"label1";
		groupBox->CashLabel->Size = System::Drawing::Size(73, 13);
		groupBox->CashLabel->TabIndex = 0;
		groupBox->CashLabel->Text = Convert::ToString(table.buy_in);
		groupBox->Controls->Add(groupBox->CashLabel);

		groupBox->CurrentBidLabel = (gcnew System::Windows::Forms::Label());
		groupBox->CurrentBidLabel->AutoSize = true;
		groupBox->CurrentBidLabel->Location = System::Drawing::Point(66, 36);
		groupBox->CurrentBidLabel->Name = L"label1";
		groupBox->CurrentBidLabel->Size = System::Drawing::Size(73, 13);
		groupBox->CurrentBidLabel->TabIndex = 0;
		groupBox->CurrentBidLabel->Text = "";
		groupBox->Controls->Add(groupBox->CurrentBidLabel);

		groupBox->WinnerButton = (gcnew System::Windows::Forms::Button());
		groupBox->WinnerButton->Location = System::Drawing::Point(119, 60);
		groupBox->WinnerButton->Name = L"WinnerButton";
		groupBox->WinnerButton->Size = System::Drawing::Size(75, 23);
		groupBox->WinnerButton->TabIndex = 10;
		groupBox->WinnerButton->Text = L"Winner";
		groupBox->WinnerButton->UseVisualStyleBackColor = true;
		groupBox->WinnerButton->Visible = false;
		groupBox->WinnerButton->Click += gcnew System::EventHandler(this, &MyForm::WinnerButton_Click);
		groupBox->Controls->Add(groupBox->WinnerButton);

		this->AddPlayerBox->Text = "";

		this->Controls->Add(groupBox);

		table.players.push_back(Player{ &table, msclr::interop::marshal_as<std::string>(groupBox->Text), table.buy_in });

		groupBox->player_number = table.players.size() - 1;

		if (number_of_players > 1) {
			StartButton->Visible = true;
		}
		//MessageBox::Show("player added", "notification", MessageBoxButtons::OK, MessageBoxIcon::Information);
		Update();
		PlayerGroupBoxes.Add(groupBox);
	}

	System::Void MyForm::CheckButton_Click(System::Object^ sender, System::EventArgs^ e) {
		current_player->check();
		FinishMove();
	}

	System::Void MyForm::CallButton_Click(System::Object^ sender, System::EventArgs^ e) {
		current_player->call();
		FinishMove();
	}

	System::Void MyForm::BidButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			current_player->bid();
			FinishMove();
		}
		catch (...) {}
	}

	System::Void MyForm::RaiseButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			current_player->raise();
			FinishMove();
		}
		catch (...) {}
	}

	System::Void MyForm::AllInButton_Click(System::Object^ sender, System::EventArgs^ e) {
		current_player->all_in();
		FinishMove();
	}

	System::Void MyForm::FoldButton_Click(System::Object^ sender, System::EventArgs^ e) {
		current_player->fold();
		FinishMove();
	}

	void MyForm::PlayerGroupBox::Update() {
		auto& player = table.players[player_number];
		CashLabel->Text = msclr::interop::marshal_as<System::String^>(std::to_string(player.cash));
		CurrentBidLabel->Text = msclr::interop::marshal_as<System::String^>(std::to_string(player.current_bid));
	}
}