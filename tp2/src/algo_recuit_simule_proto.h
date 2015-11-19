void mise_en_boite_recuit_simule(Options& options);
bool metropolis_criteria(int delta, float temperature);
struct wip_values generate_random_neighbor(struct exemplaire * e, vector<vector<int>>& sol, vector<vector<int>>& wip_sol, data_t& data);
int calculate_delta(vector<vector<int>>& current_best, vector<vector<int>>& new_try, int nb_box);
int get_occupied_volume(vector<vector<int>>& sol, int nb_box);
