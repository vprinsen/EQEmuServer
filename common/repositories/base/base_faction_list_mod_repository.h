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

#ifndef EQEMU_BASE_FACTION_LIST_MOD_REPOSITORY_H
#define EQEMU_BASE_FACTION_LIST_MOD_REPOSITORY_H

#include "../../database.h"
#include "../../strings.h"
#include <ctime>

class BaseFactionListModRepository {
public:
	struct FactionListMod {
		int         id;
		int         faction_id;
		int         mod;
		std::string mod_name;
	};

	static std::string PrimaryKey()
	{
		return std::string("id");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"id",
			"faction_id",
			"mod",
			"mod_name",
		};
	}

	static std::vector<std::string> SelectColumns()
	{
		return {
			"id",
			"faction_id",
			"mod",
			"mod_name",
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
		return std::string("faction_list_mod");
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

	static FactionListMod NewEntity()
	{
		FactionListMod entry{};

		entry.id         = 0;
		entry.faction_id = 0;
		entry.mod        = 0;
		entry.mod_name   = "";

		return entry;
	}

	static FactionListMod GetFactionListModEntry(
		const std::vector<FactionListMod> &faction_list_mods,
		int faction_list_mod_id
	)
	{
		for (auto &faction_list_mod : faction_list_mods) {
			if (faction_list_mod.id == faction_list_mod_id) {
				return faction_list_mod;
			}
		}

		return NewEntity();
	}

	static FactionListMod FindOne(
		Database& db,
		int faction_list_mod_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE id = {} LIMIT 1",
				BaseSelect(),
				faction_list_mod_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			FactionListMod entry{};

			entry.id         = atoi(row[0]);
			entry.faction_id = atoi(row[1]);
			entry.mod        = atoi(row[2]);
			entry.mod_name   = row[3] ? row[3] : "";

			return entry;
		}

		return NewEntity();
	}

	static int DeleteOne(
		Database& db,
		int faction_list_mod_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				faction_list_mod_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		Database& db,
		FactionListMod faction_list_mod_entry
	)
	{
		std::vector<std::string> update_values;

		auto columns = Columns();

		update_values.push_back(columns[1] + " = " + std::to_string(faction_list_mod_entry.faction_id));
		update_values.push_back(columns[2] + " = " + std::to_string(faction_list_mod_entry.mod));
		update_values.push_back(columns[3] + " = '" + Strings::Escape(faction_list_mod_entry.mod_name) + "'");

		auto results = db.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				Strings::Implode(", ", update_values),
				PrimaryKey(),
				faction_list_mod_entry.id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static FactionListMod InsertOne(
		Database& db,
		FactionListMod faction_list_mod_entry
	)
	{
		std::vector<std::string> insert_values;

		insert_values.push_back(std::to_string(faction_list_mod_entry.id));
		insert_values.push_back(std::to_string(faction_list_mod_entry.faction_id));
		insert_values.push_back(std::to_string(faction_list_mod_entry.mod));
		insert_values.push_back("'" + Strings::Escape(faction_list_mod_entry.mod_name) + "'");

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				Strings::Implode(",", insert_values)
			)
		);

		if (results.Success()) {
			faction_list_mod_entry.id = results.LastInsertedID();
			return faction_list_mod_entry;
		}

		faction_list_mod_entry = NewEntity();

		return faction_list_mod_entry;
	}

	static int InsertMany(
		Database& db,
		std::vector<FactionListMod> faction_list_mod_entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &faction_list_mod_entry: faction_list_mod_entries) {
			std::vector<std::string> insert_values;

			insert_values.push_back(std::to_string(faction_list_mod_entry.id));
			insert_values.push_back(std::to_string(faction_list_mod_entry.faction_id));
			insert_values.push_back(std::to_string(faction_list_mod_entry.mod));
			insert_values.push_back("'" + Strings::Escape(faction_list_mod_entry.mod_name) + "'");

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

	static std::vector<FactionListMod> All(Database& db)
	{
		std::vector<FactionListMod> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			FactionListMod entry{};

			entry.id         = atoi(row[0]);
			entry.faction_id = atoi(row[1]);
			entry.mod        = atoi(row[2]);
			entry.mod_name   = row[3] ? row[3] : "";

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static std::vector<FactionListMod> GetWhere(Database& db, std::string where_filter)
	{
		std::vector<FactionListMod> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			FactionListMod entry{};

			entry.id         = atoi(row[0]);
			entry.faction_id = atoi(row[1]);
			entry.mod        = atoi(row[2]);
			entry.mod_name   = row[3] ? row[3] : "";

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

#endif //EQEMU_BASE_FACTION_LIST_MOD_REPOSITORY_H
