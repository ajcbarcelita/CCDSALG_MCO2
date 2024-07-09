import networkx as nx

def main():
    
    # This is the main menu of the program.
    # Add a part here that allows the user to import a .txt file containing data for a social graph.
    # If the .txt file is not found, display an error message, BUT not exit the program.
    # If the .txt file is found, display a success message, and prompt the user to choose between an
    # ADJACENCY LIST or MATRIX for the social graph.
    # Choosing either will display the social graph in the chosen format, and will prompt the user to the main menu.

    while choice != 3:
        print("\n\t==== MAIN MENU ====")
        print("[1] Display friend list.")
        print("[2] Display connections.")
        print("[3] Exit.")
        try:
            choice = int(input("Enter choice: "))
        except ValueError:
            print("Input is not of type int. Please try again.")
            continue

        if choice == 1:
            # This function accepts an ID number as a parameter.
            # If valid, display total number of friends and list of friends.
            # If not, display an error message, BUT not exit the program.
            pass
        elif choice == 2:
            # This function accepts 2 different ID numbers as parameters.
            # If both ID numbers exist, display the connection/path between the two.
            # If any/both ID numbers does not exist, display an error message, BUT not exit the program.
            pass
        elif choice == 3:
            print("Exiting the program...")
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()