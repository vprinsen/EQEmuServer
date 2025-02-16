/**
 * DO NOT MODIFY THIS FILE
 *
 * This repository was automatically generated and is NOT to be modified directly.
 * Any repository modifications are meant to be made to the repository extending the base.
 * Any modifications to base repositories are to be made by the generator only
 *
 * @generator ./utils/scripts/generators/repository-generator.pl
 * @docs https://eqemu.gitbook.io/server/in-development/developer-area/repositories
 */

#ifndef EQEMU_BASE_CHARACTER_ALTERNATE_ABILITIES_REPOSITORY_H
#define EQEMU_BASE_CHARACTER_ALTERNATE_ABILITIES_REPOSITORY_H

#include "../../database.h"
#include "../../strings.h"
#include <ctime>

class BaseCharacterAlternateAbilitiesRepository {
public:
	struct CharacterAlternateAbilities {
		int id;
		int aa_id;
		int aa_value;
		int charges;
	};

	static std::string PrimaryKey()
	{
		return std::string("id");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"id",
			"aa_id",
			"aa_value",
			"charges",
		};
	}

	static std::vector<std::string> SelectColumns()
	{
		return {
			"id",
			"aa_id",
			"aa_value",
			"charges",
		};
	}

	static std::string ColumnsRaw()
	{
		return std::string(Strings::Implode(", ", Columns()));
	}

	static std::string SelectColumnsRaw()
	{
		return std::string(Strings::Implode(", ", SelectColumns()));
	}

	static std::string TableName()
	{
		return std::string("character_alternate_abilities");
	}

	static std::string BaseSelect()
	{
		return fmt::format(
			"SELECT {} FROM {}",
			SelectColumnsRaw(),
			TableName()
		);
	}

	static std::string BaseInsert()
	{
		return fmt::format(
			"INSERT INTO {} ({}) ",
			TableName(),
			ColumnsRaw()
		);
	}

	static CharacterAlternateAbilities NewEntity()
	{
		CharacterAlternateAbilities entry{};

		entry.id       = 0;
		entry.aa_id    = 0;
		entry.aa_value = 0;
		entry.charges  = 0;

		return entry;
	}

	static CharacterAlternateAbilities GetCharacterAlternateAbilitiesEntry(
		const std::vector<CharacterAlternateAbilities> &character_alternate_abilitiess,
		int character_alternate_abilities_id
	)
	{
		for (auto &character_alternate_abilities : character_alternate_abilitiess) {
			if (character_alternate_abilities.id == character_alternate_abilities_id) {
				return character_alternate_abilities;
			}
		}

		return NewEntity();
	}

	static CharacterAlternateAbilities FindOne(
		Database& db,
		int character_alternate_abilities_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE id = {} LIMIT 1",
				BaseSelect(),
				character_alternate_abilities_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			CharacterAlternateAbilities entry{};

			entry.id       = atoi(row[0]);
			entry.aa_id    = atoi(row[1]);
			entry.aa_value = atoi(row[2]);
			entry.charges  = atoi(row[3]);

			return entry;
		}

		return NewEntity();
	}

	static int DeleteOne(
		Database& db,
		int character_alternate_abilities_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				character_alternate_abilities_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		Database& db,
		CharacterAlternateAbilities character_alternate_abilities_entry
	)
	{
		std::vector<std::string> update_values;

		auto columns = Columns();

		update_values.push_back(columns[0] + " = " + std::to_string(character_alternate_abilities_entry.id));
		update_values.push_back(columns[1] + " = " + std::to_string(character_alternate_abilities_entry.aa_id));
		update_values.push_back(columns[2] + " = " + std::to_string(character_alternate_abilities_entry.aa_value));
		update_values.push_back(columns[3] + " = " + std::to_string(character_alternate_abilities_entry.charges));

		auto results = db.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				Strings::Implode(", ", update_values),
				PrimaryKey(),
				character_alternate_abilities_entry.id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static CharacterAlternateAbilities InsertOne(
		Database& db,
		CharacterAlternateAbilities character_alternate_abilities_entry
	)
	{
		std::vector<std::string> insert_values;

		insert_values.push_back(std::to_string(character_alternate_abilities_entry.id));
		insert_values.push_back(std::to_string(character_alternate_abilities_entry.aa_id));
		insert_values.push_back(std::to_string(character_alternate_abilities_entry.aa_value));
		insert_values.push_back(std::to_string(character_alternate_abilities_entry.charges));

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				Strings::Implode(",", insert_values)
			)
		);

		if (results.Success()) {
			character_alternate_abilities_entry.id = results.LastInsertedID();
			return character_alternate_abilities_entry;
		}

		character_alternate_abilities_entry = NewEntity();

		return character_alternate_abilities_entry;
	}

	static int InsertMany(
		Database& db,
		std::vector<CharacterAlternateAbilities> character_alternate_abilities_entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &character_alternate_abilities_entry: character_alternate_abilities_entries) {
			std::vector<std::string> insert_values;

			insert_values.push_back(std::to_string(character_alternate_abilities_entry.id));
			insert_values.push_back(std::to_string(character_alternate_abilities_entry.aa_id));
			insert_values.push_back(std::to_string(character_alternate_abilities_entry.aa_value));
			insert_values.push_back(std::to_string(character_alternate_abilities_entry.charges));

			insert_chunks.push_back("(" + Strings::Implode(",", insert_values) + ")");
		}

		std::vector<std::string> insert_values;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES {}",
				BaseInsert(),
				Strings::Implode(",", insert_chunks)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static std::vector<CharacterAlternateAbilities> All(Database& db)
	{
		std::vector<CharacterAlternateAbilities> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			CharacterAlternateAbilities entry{};

			entry.id       = atoi(row[0]);
			entry.aa_id    = atoi(row[1]);
			entry.aa_value = atoi(row[2]);
			entry.charges  = atoi(row[3]);

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static std::vector<CharacterAlternateAbilities> GetWhere(Database& db, std::string where_filter)
	{
		std::vector<CharacterAlternateAbilities> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			CharacterAlternateAbilities entry{};

			entry.id       = atoi(row[0]);
			entry.aa_id    = atoi(row[1]);
			entry.aa_value = atoi(row[2]);
			entry.charges  = atoi(row[3]);

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static int DeleteWhere(Database& db, std::string where_filter)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {}",
				TableName(),
				where_filter
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int Truncate(Database& db)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"TRUNCATE TABLE {}",
				TableName()
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

};

#endif //EQEMU_BASE_CHARACTER_ALTERNATE_ABILITIES_REPOSITORY_H
